#ifdef _WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "pomelo.h"

#define MAX_LINE_CHARS 1024

#define END_STR "bye"

const char *ip = "192.168.1.116";
int port = 3010;
int working = 0;

void on_connected(pc_connect_t *conn_req, int status){
  printf("data = %p\n", conn_req->data);
  pc_connect_req_destroy(conn_req);

  if(-1==status){
    printf("Connected error.\n");
  } else {
    working = 1;
  }

}

// request callback
void on_request_cb(pc_request_t *req, int status, json_t *resp) {
  if(status == -1) {
    printf("Fail to send request to server.\n");
  } else if(status == 0) {
    printf("server echo: %s\n",
           json_string_value(json_object_get(resp, "body")));
  }

  // release relative resource with pc_request_t
  json_t *msg = req->msg;
  json_decref(msg);
  pc_request_destroy(req);
}

void do_request(pc_client_t *client, const char *input) {
  // compose request
  const char *route = "connector.helloHandler.echo";
  json_t *msg = json_object();
  json_t *str = json_string(input);
  json_object_set(msg, "body", str);
  // decref for json object
  json_decref(str);

  pc_request_t *request = pc_request_new();
  pc_request(client, request, route, msg, on_request_cb);
}

// disconnect event callback.
void on_close(pc_client_t *client, const char *event, void *data) {
  printf("client closed: %d.\n", client->state);
}


int main() {
  // create a client instance.
  pc_client_t *client = pc_client_new();

  struct sockaddr_in address;

  memset(&address, 0, sizeof(struct sockaddr_in));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(ip);

  pc_connect_t *conn_req = pc_connect_req_new(&address);
  //~ bring some private date on
  conn_req->data = (void*)0x2013;

  // add some event callback.
  pc_add_listener(client, PC_EVENT_DISCONNECT, on_close);

  // try to connect to server.
  if(pc_client_connect2(client, conn_req, on_connected)) {
    printf("fail to connect server.\n");
	pc_connect_req_destroy(conn_req);
    pc_client_destroy(client);
    return 1;
  }

  char input[MAX_LINE_CHARS];

  printf("Input a line to send message to server and input `bye` to exit.\n");
  while(1) {
    scanf("%s", input);
    if(!strcmp(input, END_STR)) {
      break;
    }
	if( working ){
	    do_request(client, input);
	} else {
		printf("Not connected yet, please quit and restart.\n");
	}
  }

  // release the client
  pc_client_destroy(client);

  return 0;
}
