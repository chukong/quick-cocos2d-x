#ifdef _WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "pomelo.h"

const char *ip = "127.0.0.1";
int port = 3010;

// notified callback
void on_notified(pc_notify_t *req, int status) {
  if(status == -1) {
    printf("Fail to send notify to server.\n");
  } else {
    printf("Notify finished.\n");
  }

  // release resources
  json_t *msg = req->msg;
  json_decref(msg);
  pc_notify_destroy(req);
}

// server push message "onHey" callback.
void on_hey(pc_client_t *client, const char *event, void *data) {
  json_t *push_msg = (json_t *)data;
  const char *json_str = json_dumps(push_msg, 0);
  printf("on event: %s, serve push msg: %s\n", event, json_str);
  free((void *)json_str);

  // stop the working thread.
  pc_client_stop(client);
}

// disconnect event callback.
void on_close(pc_client_t *client, const char *event, void *data) {
  printf("client closed: %d.\n", client->state);
}

void do_notify(pc_client_t *client) {
  // compose notify.
  const char *route = "connector.helloHandler.hello";
  json_t *msg = json_object();
  json_t *json_str = json_string("hello");
  json_object_set(msg, "msg", json_str);
  // decref json string
  json_decref(json_str);

  pc_notify_t *notify = pc_notify_new();
  pc_notify(client, notify, route, msg, on_notified);
}

int main() {
  // create a client instance.
  pc_client_t *client = pc_client_new();

  struct sockaddr_in address;

  memset(&address, 0, sizeof(struct sockaddr_in));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(ip);

  // add some event callback.
  pc_add_listener(client, "onHey", on_hey);
  pc_add_listener(client, PC_EVENT_DISCONNECT, on_close);

  // try to connect to server.
  if(pc_client_connect(client, &address)) {
    printf("fail to connect server.\n");
    pc_client_destroy(client);
    return 1;
  }

  do_notify(client);

  // main thread has nothing to do and wait until child thread return.
  pc_client_join(client);

  // release the client
  pc_client_destroy(client);

  return 0;
}
