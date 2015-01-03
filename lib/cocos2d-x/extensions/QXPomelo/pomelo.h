#ifndef POMELO_CLIENT_H
#define POMELO_CLIENT_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
  /* Windows - set up dll import/export decorators. */
# if defined(BUILDING_PC_SHARED)
    /* Building shared library. */
#   define PC_EXTERN __declspec(dllexport)
# elif defined(USING_PC_SHARED)
    /* Using shared library. */
#   define PC_EXTERN __declspec(dllimport)
# else
    /* Building static library. */
#   define PC_EXTERN /* nothing */
# endif
#elif __GNUC__ >= 4
# define PC_EXTERN __attribute__((visibility("default")))
#else
# define PC_EXTERN /* nothing */
#endif

#include "uv.h"
#include "jansson.h"
#include "pomelo-private/map.h"

#define PC_TYPE "c"
#define PC_VERSION "0.0.1"

#define PC_EVENT_DISCONNECT "disconnect"
#define PC_EVENT_KICK "onKick"

typedef struct pc_client_s pc_client_t;
typedef struct pc_listener_s pc_listener_t;
typedef struct pc_req_s pc_req_t;
typedef struct pc_connect_s pc_connect_t;
typedef struct pc_tcp_req_s pc_tcp_req_t;
typedef struct pc_request_s pc_request_t;
typedef struct pc_notify_s pc_notify_t;
typedef struct pc_msg_s pc_msg_t;
typedef struct pc_pkg_parser_s pc_pkg_parser_t;
typedef uv_buf_t pc_buf_t;

/**
 * State machine for Pomelo package parser
 */
typedef enum {
  PC_PKG_HEAD = 1,        /* parsing header */
  PC_PKG_BODY,            /* parsing body */
  PC_PKG_CLOSED
} pc_pkg_parser_state;

/**
 * Package type of Pomelo package
 */
typedef enum pc_pkg_type_e {
  PC_PKG_HANDSHAKE = 1,
  PC_PKG_HANDSHAKE_ACK,
  PC_PKG_HEARBEAT,
  PC_PKG_DATA,
  PC_PKG_KICK
} pc_pkg_type;

/**
 * Pomelo client states.
 */
typedef enum {
  PC_ST_INITED = 1,
  PC_ST_CONNECTING,
  PC_ST_CONNECTED,
  PC_ST_WORKING,
  PC_ST_CLOSED
} pc_client_state;

/**
 * Pomelo client async request types.
 */
typedef enum {
  PC_CONNECT,
  PC_REQUEST,
  PC_NOTIFY
} pc_req_type;

/**
 * State of transport.
 */
typedef enum {
  PC_TP_ST_INITED = 1,
  PC_TP_ST_CONNECTING,
  PC_TP_ST_WORKING,
  PC_TP_ST_CLOSED
} pc_transport_state;

/**
 * Callbacks
 */

/**
 * Event callback.
 *
 * @param  client client instance that fire the event.
 * @param  event  event name that registered before.
 * @param  data   attach data of the event.
 */
typedef void (*pc_event_cb)(pc_client_t *client, const char *event, void *data);

/**
 * Connection established callback.
 *
 * @param  req    connect request.
 * @param  status connect status. 0 for ok and -1 for error.
 */
typedef void (*pc_connect_cb)(pc_connect_t* req, int status);

/**
 * Request callback.
 *
 * @param  req    request instance.
 * @param  status request status. 0 for ok and -1 for error.
 * @param  resp   response message from server, NULL for error.
 */
typedef void (*pc_request_cb)(pc_request_t *req, int status, json_t *resp);

/**
 * Notify callback.
 *
 * @param  req    request instance.
 * @param  status notify status. o for ok and -1 for error.
 */
typedef void (*pc_notify_cb)(pc_notify_t *req, int status);

/**
 * Handshake callback for client which would be fired during handshake phase and
 * passing the customized handshake information from server.
 *
 * @param  client client instance.
 * @param  msg    customized handshake information from server.
 * @return        0 for ok and -1 for error and terminate the connection.
 */
typedef int (*pc_handshake_cb)(pc_client_t *client, json_t *msg);

/**
 * Message parse callback which would be fired when a new message arrived.
 *
 * @param client client instance.
 * @param data   original message data in bytes.
 * @param len    length of the data.
 * @return       the parse result or NULL for error.
 */
typedef pc_msg_t *(*pc_msg_parse_cb)(pc_client_t *client, const char *data,
    size_t len);

/**
 * Message parse done callback which would be fired when the the message has
 * processed to release the resources created in the message parsing phase.
 *
 * @param  client client instance.
 * @param  msg    message instance.
 */
typedef void (*pc_msg_parse_done_cb)(pc_client_t *client, pc_msg_t *msg);

/**
 * Message encode callback which would be fired when a new request or notify is
 * emitted. This is the place to customized the message layer encode and the
 * result would be delivered on the Pomelo package layer.
 *
 * @param  client client instance.
 * @param  reqId  request id, positive for request and 0 for notify.
 * @param  route  route string.
 * @param  msg    message content.
 * @return        encode result, buf.len = -1 for error.
 */
typedef pc_buf_t (*pc_msg_encode_cb)(pc_client_t *client, uint32_t reqId,
                                     const char* route, json_t *msg);

/**
 * Message encode done callback which would be fired when the encode data has
 * been delivered or meeting some error to release the resources created during
 * the encode phase.
 *
 * @param  client client instance.
 * @param  buf    encode result.
 */
typedef void (*pc_msg_encode_done_cb)(pc_client_t *client, pc_buf_t buf);

/**
 * Simple structure for memory block.
 * The pc_buf_s is cheap and could be passed by value.
 */
struct pc_buf_s {
  char *base;
  size_t len;
};

/**
 * Transport structure.
 */
typedef struct {
  pc_client_t *client;
  uv_tcp_t *socket;
  pc_transport_state state;
} pc_transport_t;

#define PC_REQ_FIELDS                                                         \
  /* private */                                                               \
  pc_client_t *client;                                                        \
  pc_transport_t *transport;                                                  \
  pc_req_type type;                                                           \
  void *data;                                                                 \

#define PC_TCP_REQ_FIELDS                                                     \
  /* public */                                                                \
  const char *route;                                                          \
  json_t *msg;                                                                \

/**
 * The abstract base class of all async request in Pomelo client.
 */
struct pc_req_s {
  PC_REQ_FIELDS
};

/**
 * The abstract base class of all tcp async request and a subclass of pc_req_t.
 */
struct pc_tcp_req_s {
  PC_REQ_FIELDS
  PC_TCP_REQ_FIELDS
};

/**
 * Pomelo client instance
 */
struct pc_client_s {
  /* public */
  pc_client_state state;
  /* private */
  uv_loop_t *uv_loop;
  pc_transport_t *transport;
  pc_map_t *listeners;
  pc_map_t *requests;
  pc_pkg_parser_t *pkg_parser;
  int heartbeat;
  int timeout;
  json_t *handshake_opts;
  pc_handshake_cb handshake_cb;
  pc_connect_t *conn_req;
  json_t *route_to_code;
  json_t *code_to_route;
  json_t *server_protos;
  json_t *client_protos;
  pc_msg_parse_cb parse_msg;
  pc_msg_parse_done_cb parse_msg_done;
  pc_msg_encode_cb encode_msg;
  pc_msg_encode_done_cb encode_msg_done;
  uv_timer_t *heartbeat_timer;
  uv_timer_t *timeout_timer;
  uv_async_t *close_async;
  uv_mutex_t mutex;
  uv_cond_t cond;
  uv_mutex_t listener_mutex;
  uv_thread_t worker;
};

/**
 * Connect request class is a subclass of pc_req_t.
 * Connect is the async context for a connection request to server.
 */
struct pc_connect_s {
  PC_REQ_FIELDS
  /* public */
  struct sockaddr_in *address;
  pc_connect_cb cb;
  /* private */
  uv_tcp_t *socket;
};

/**
 * Pomelo request class is a subclass of pc_tcp_req_t.
 * Request is the async context for a Pomelo request to server.
 */
struct pc_request_s {
  PC_REQ_FIELDS
  PC_TCP_REQ_FIELDS
  uint32_t id;
  pc_request_cb cb;
  ngx_queue_t queue;
};

/**
 * Pomelo notify class is a subclass of pc_tcp_req_t.
 * Notify is the async context for a Pomelo notify to server.
 */
struct pc_notify_s {
  PC_REQ_FIELDS
  PC_TCP_REQ_FIELDS
  pc_notify_cb cb;
};

/**
 * Message structure.
 */
struct pc_msg_s {
  uint32_t id;
  const char* route;
  json_t *msg;
};

/**
 * Create and initiate Pomelo client intance.
 *
 * @return Pomelo client instance
 */
pc_client_t *pc_client_new();

/**
 * Stop the connection of the client. It is suitable for calling in the child
 * thread and the main thread called the pc_client_join funtion the wait the
 * worker child thread return.
 *
 * @param client client instance.
 */
void pc_client_stop(pc_client_t *client);

/**
 * Destroy and disconnect the connection of the client instance.
 *
 * @param client client instance.
 */
void pc_client_destroy(pc_client_t *client);

/**
 * Join and wait the worker child thread return. It is suitable for the
 * situation that the main thread has nothing to do after the connction
 * established.
 *
 * @param  client client instance.
 * @return        0 for ok or error code for error.
 */
int pc_client_join(pc_client_t *client);

/**
 * Create and initiate a request instance.
 *
 * @return     req request instance
 */
pc_request_t *pc_request_new();

/**
 * Destroy and release inner resource of a request instance.
 *
 * @param req request instance to be destroied.
 */
void pc_request_destroy(pc_request_t *req);

/**
 * Connect the client to the server which would create a worker child thread
 * and connect to the server.
 *
 * @param  client client instance.
 * @param  addr   server address.
 * @return        0 or -1.
 */
int pc_client_connect(pc_client_t *client, struct sockaddr_in *addr);


/*
 * Connect the client to server just like pc_client_connect,
 * except that it's the asynchronous version for it.
 * The user should be responsible to conn_req's allocation, initialization and reclamation
 *
 * @param client client instance
 * @param conn_req connect request which are allocated and initialized by pc_connect_req_new
 * @return 0 or -1
 */
 int pc_client_connect2(pc_client_t *client, pc_connect_t *conn_req, pc_connect_cb cb);


/*
 *
 * Use for async connection
 * 
 * @param addr address to which the connection is made
 * @return an instance of pc_connect_t, which should be released manually by user.
 */
pc_connect_t* pc_connect_req_new(struct sockaddr_in *addr);

/*
 * Destroy instance of pc_connect_t
 *
 * @param conn_req pc_connect_t instance
 * @return none
 */
void pc_connect_req_destroy(pc_connect_t *conn_req);

/**
 * Send rerquest to server.
 * The message object and request object must keep
 * until the pc_request_cb invoked.
 *
 * @param  client Pomelo client instance
 * @param  req    initiated request instance
 * @param  route  route string
 * @param  msg    message object
 * @param  cb     request callback
 * @return        0 or -1
 */
int pc_request(pc_client_t *client, pc_request_t *req, const char *route,
               json_t *msg, pc_request_cb cb);

/**
 * Create and initiate notify instance.
 *
 * @return   notify instance
 */
pc_notify_t *pc_notify_new();

/**
 * Destroy and release inner resource of a notify instance.
 *
 * @param req notify instance to be destroied.
 */
void pc_notify_destroy(pc_notify_t *req);

/**
 * Send notify to server.
 * The message object and notify object must keep
 * until the pc_notify_cb invoked.
 *
 * @param  client Pomelo client instance
 * @param  req    initiated notify instance
 * @param  route  route string
 * @param  msg    message object
 * @param  cb     notify callback
 * @return        0 or -1
 */
int pc_notify(pc_client_t *client, pc_notify_t *req, const char *route,
              json_t *msg, pc_notify_cb cb);

/**
 * Register a listener in the client.
 *
 * @param  client   client instance.
 * @param  event    event name.
 * @param  event_cb event callback.
 * @return          0 or -1.
 */
int pc_add_listener(pc_client_t *client, const char *event,
                    pc_event_cb event_cb);

/**
 * Remove a listener in the client.
 *
 * @param  client   client instance.
 * @param  event    event name.
 * @param  event_cb event callback.
 * @return          void.
 */
void pc_remove_listener(pc_client_t *client, const char *event,
                    pc_event_cb event_cb);

/**
 * Emit a event from the client.
 *
 * @param client client instance.
 * @param event  event name.
 * @param data   attach data of the event.
 */
void pc_emit_event(pc_client_t *client, const char *event, void *data);

/* Don't export the private CPP symbols. */
#undef PC_TCP_REQ_FIELDS
#undef PC_REQ_FIELDS

#ifdef __cplusplus
}
#endif
#endif /* POMELO_CLIENT_H */
