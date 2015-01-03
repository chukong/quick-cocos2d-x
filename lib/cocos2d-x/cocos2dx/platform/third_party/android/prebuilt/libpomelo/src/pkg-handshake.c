#include <string.h>
#include "pomelo.h"
#include "pomelo-protocol/package.h"
#include "pomelo-private/jansson-memory.h"

extern int pc__binary_write(pc_client_t *client, const char *data, size_t len,
                     uv_write_cb cb);

static int pc__handshake_ack(pc_client_t *client);
static void pc__handshake_req_cb(uv_write_t* req, int status);
static void pc__handshake_ack_cb(uv_write_t* req, int status);

static void pc__load_file(pc_client_t *client, const char *name, json_t **dest);
static void pc__dump_file(pc_client_t *client, const char *name, json_t *src);

int pc__handshake_req(pc_client_t *client) {
  json_t *handshake_opts = client->handshake_opts;
  json_t *body = json_object();
  json_error_t err;
  const char *data = NULL;

  if(body == NULL) {
    fprintf(stderr, "Fail to create json_t for handshake request.\n");
    return -1;
  }

  // compose handshake package
  json_t *sys = json_object();
  if(sys == NULL) {
    fprintf(stderr, "Fail to create json_t for handshake request.\n");
    goto error;
  }

  json_object_set(body, "sys", sys);
  json_decref(sys);

  json_t *json_type = json_string(PC_TYPE);
  json_t *json_version = json_string(PC_VERSION);
  json_object_set(sys, "type", json_type);
  json_object_set(sys, "version", json_version);

  json_t *proto = NULL;
  if(!client->proto_ver) {
    pc__load_file(client, PC_PROTO_VERSION, &proto);
    if(proto) {
      client->proto_ver = json_object_get(proto, PC_PROTO_VERSION);
      json_incref(client->proto_ver);
      json_object_set(sys, PC_PROTO_VERSION, client->proto_ver);
    }
  } else {
    json_object_set(sys, PC_PROTO_VERSION, client->proto_ver);
  }


  json_decref(json_type);
  json_decref(json_version);
  json_decref(proto);

  if(handshake_opts) {
    json_t *user = json_object_get(handshake_opts, "user");
    if(user) {
      json_object_set(body, "user", user);
    }
  }

  data = json_dumps(body, JSON_COMPACT);
  if(data == NULL) {
    fprintf(stderr, "Fail to compose Pomelo handshake package.\n");
    goto error;
  }

  pc_buf_t buf = pc_pkg_encode(PC_PKG_HANDSHAKE, data, strlen(data));
  if(pc__binary_write(client, buf.base, buf.len, pc__handshake_req_cb)) {
    fprintf(stderr, "Fail to send handshake request.\n");
    goto error;
  }

  pc_jsonp_free((void *)data);
  json_decref(body);

  return 0;
error:
  if(data) pc_jsonp_free((void *)data);
  if(body) json_decref(body);
  return -1;
}

int pc__handshake_resp(pc_client_t *client,
                       const char *data, size_t len) {
  json_error_t error;
  json_t *res = json_loadb(data, len, 0, &error);

  if(res == NULL) {
    fprintf(stderr, "Fail to parse handshake package. %s\n", error.text);
    goto error;
  }

  json_int_t code = json_integer_value(json_object_get(res, "code"));
  if(code != PC_HANDSHAKE_OK) {
    fprintf(stderr, "Handshake fail, code: %d.\n", (int)code);
    goto error;
  }

  json_t *sys = json_object_get(res, "sys");
  if(sys) {
    // setup heartbeat
    json_int_t hb = json_integer_value(json_object_get(sys, "heartbeat"));
    if(hb <= 0) {
      // no need heartbeat
      client->heartbeat = -1;
      client->timeout = -1;
    } else {
        client->heartbeat = hb * 1000;
      client->timeout = client->heartbeat * PC_HEARTBEAT_TIMEOUT_FACTOR;
      uv_timer_set_repeat(client->heartbeat_timer, client->heartbeat);
      uv_timer_set_repeat(client->timeout_timer, client->timeout);
    }

    // setup route dictionary
    json_t *dict = json_object_get(sys, "dict");
    if(dict) {
      client->route_to_code = dict;
      json_incref(dict);
      client->code_to_route = json_object();
      const char *key;
      json_t *value;
      char code_str[16];
      json_object_foreach(dict, key, value) {
        memset(code_str, 0, 16);
        sprintf(code_str, "%u", ((int)json_integer_value(value) & 0xff));
        json_t *json_key = json_string(key);
        json_object_set(client->code_to_route, code_str, json_key);
        json_decref(json_key);
      }
    }

    // setup protobuf data definition
    json_t *useProto = json_object_get(sys, "useProto");
    if(useProto) {
      json_t *protos = json_object_get(sys, "protos");
      if(protos) {
        if(client->server_protos) {
          json_decref(client->server_protos);
        }
        client->server_protos = json_object_get(protos, "server");
        if(client->client_protos) {
          json_decref(client->client_protos);
        }
        client->client_protos = json_object_get(protos, "client");
        json_incref(client->server_protos);
        json_incref(client->client_protos);

        json_t *t = json_object();
        json_object_set(t, PC_PROTO_VERSION, json_object_get(protos, "version"));
        pc__dump_file(client, PC_PROTO_VERSION, t);
        json_decref(t);

        pc__dump_file(client, PC_PROTO_SERVER, client->server_protos);
        pc__dump_file(client, PC_PROTO_CLIENT, client->client_protos);
      } else {
        if(!client->server_protos) {
          pc__load_file(client, PC_PROTO_SERVER, &client->server_protos);
        }
        if(!client->client_protos) {
          pc__load_file(client, PC_PROTO_CLIENT, &client->client_protos);
        }
      }
    } else {
      if(client->server_protos) {
        json_decref(client->server_protos);
        client->server_protos = NULL;
      }
      if(client->client_protos) {
        json_decref(client->client_protos);
        client->client_protos = NULL;
      }
      if(client->proto_ver) {
        json_decref(client->proto_ver);
        client->proto_ver = NULL;
      }
    }
  }

  json_t *user = json_object_get(res, "user");
  int status = 0;
  if(client->handshake_cb) {
    status = client->handshake_cb(client, user);
  }

  // release json parse result
  json_decref(res);

  if(!status) {
    pc__handshake_ack(client);
  }

  return 0;

error:
  json_decref(res);
  return -1;
}

static int pc__handshake_ack(pc_client_t *client) {
  pc_buf_t buf = pc_pkg_encode(PC_PKG_HANDSHAKE_ACK, NULL, 0);
  if(buf.len == -1) {
    fprintf(stderr, "Fail to encode handshake ack package.\n");
    goto error;
  }

  if(pc__binary_write(client, buf.base, buf.len, pc__handshake_ack_cb)) {
    fprintf(stderr, "Fail to send handshake ack.\n");
    goto error;
  }

  return 0;

error:
  if(buf.len != -1) free(buf.base);
  return -1;
}

static void pc__handshake_req_cb(uv_write_t* req, int status) {
  void **data = (void **)req->data;
  pc_transport_t *transport = (pc_transport_t *)data[0];
  pc_client_t *client = transport->client;
  char *base = (char *)data[1];

  free(base);
  free(data);
  free(req);

  if(PC_TP_ST_WORKING != transport->state) {
    fprintf(stderr, "Invalid transport state for handshake req cb: %d.\n",
            transport->state);
    return;
  }

  if(status == -1) {
    fprintf(stderr, "Fail to write handshake request async, %s.\n",
            uv_err_name(uv_last_error(client->uv_loop)));
    pc_client_stop(client);
    if(client->conn_req) {
      pc_connect_t *conn_req = client->conn_req;
      client->conn_req = NULL;
      conn_req->cb(conn_req, status);
    }
  }
}

static void pc__handshake_ack_cb(uv_write_t* req, int status) {
  void **data = (void **)req->data;
  pc_transport_t *transport = (pc_transport_t *)data[0];
  pc_client_t *client = transport->client;
  char *base = (char *)data[1];

  free(base);
  free(data);
  free(req);

  if(PC_TP_ST_WORKING != transport->state) {
    fprintf(stderr, "Invalid transport state for handshake ack cb: %d.\n",
            transport->state);
    return;
  }

  if(status == -1) {
    fprintf(stderr, "Fail to write handshake ack async, %s.\n",
            uv_err_name(uv_last_error(client->uv_loop)));
    pc_client_stop(client);
  } else {
    client->state = PC_ST_WORKING;
  }

  if(client->conn_req) {
    pc_connect_t *conn_req = client->conn_req;
    client->conn_req = NULL;
    conn_req->cb(conn_req, status);
  }
}

static void pc__load_file(pc_client_t *client, const char *name, json_t **dest) {
  json_error_t err;
  if(client->proto_event_cb) {
    client->proto_event_cb(client, PC_PROTO_OP_READ, name, (void*)dest);
  } else if(client->proto_read_dir) {
    char *path = (char*)malloc(strlen(client->proto_read_dir) + 1 + strlen(name) + 1);
    strcpy(path, client->proto_read_dir);
    strcat(path, "/"); 
    strcat(path, name);
    *dest = json_load_file(path, 0, &err);
    free(path);
    path = NULL;
  } else {
    *dest = json_load_file(name, 0, &err);
  }
}

static void pc__dump_file(pc_client_t *client, const char *name, json_t *src) {
  if(client->proto_event_cb) {
    client->proto_event_cb(client, PC_PROTO_OP_WRITE, name, (void*)src);
  } else if(client->proto_write_dir) {
    char *path = (char*)malloc(strlen(client->proto_read_dir) + 1 + strlen(name) + 1);
    strcpy(path, client->proto_read_dir);
    strcat(path, "/");
    strcat(path, name);
    json_dump_file(src, path, 0);
    free(path);
    path = NULL;
  } else {
    json_dump_file(src, name, 0);
  }
}
