#ifndef PC_INTERNAL_H
#define PC_INTERNAL_H

#include "pomelo.h"

#ifdef _WIN32
  #include <winsock2.h>
#else
  #include <netinet/in.h>
  #include <unistd.h>
#endif
/**
 * Callback for received a handshake response from server.
 *
 * @param  client client instance.
 * @param  data   handshake response in bytes.
 * @param  len    length of data.
 * @return        0 or -1
 */
int pc__handshake_resp(pc_client_t *client, const char *data, size_t len);

/**
 * Callback for received a heartbeat from server.
 *
 * @param  client client instance.
 * @return        0 or -1
 */
int pc__heartbeat(pc_client_t *client);

/**
 * Callback for heartbeat interval event in which would send a heartbeat request
 * to server.
 *
 * @param heartbeat_timer timer for heartbeat interval.
 * @param status          0 or -1
 */
void pc__heartbeat_cb(uv_timer_t* heartbeat_timer, int status);

/**
 * Callback for heartbeat timeout event.
 *
 * @param timeout_timer timer for heartbeat timeout.
 * @param status        0 or -1
 */
void pc__timeout_cb(uv_timer_t* timeout_timer, int status);

/**
 * Create and initiate connect request instance.
 *
 * @param  address server address
 * @return         connect request instance
 */
pc_connect_t *pc_connect_req_new(struct sockaddr_in *address);

/**
 * Destroy a connect request instance and release inner resources.
 *
 * @param  req connect request instance.
 */
void pc_connect_req_destroy(pc_connect_t *req);

/**
 * Connect Pomelo client to server.
 *
 * @param  client         Pomelo client instance
 * @param  req            connection request
 * @param  handshake_opts handshake options send to server
 * @param  cb             connection established callback
 * @return                result code, 0 for ok, -1 for error
 */
int pc_connect(pc_client_t *client, pc_connect_t *req,
               json_t *handshake_opts, pc_connect_cb cb);

/**
 * Disconnect Pomelo client and reset all status back to initialted.
 *
 * @param client Pomelo client instance.
 */
void pc_disconnect(pc_client_t *client, int reset);

/**
 * Start the uv loop in client.
 *
 * @param  client client instance.
 * @return        0 or -1
 */
int pc_run(pc_client_t *client);

/**
 * Wait a condition notify of client, used internal only.
 *
 * @param client  client instance.
 * @param timeout wait timeout value or 0 for wait forever.
 */
void pc__cond_wait(pc_client_t *client, uint64_t timeout);

/**
 * Do a condition broadcast, used internal only.
 *
 * @param client client instance.
 */
void pc__cond_broadcast(pc_client_t *client);

/**
 * Callback for server connected.
 *
 * @param req    connect request.
 * @param status 0 or -1
 */
void pc__client_connected_cb(pc_connect_t* req, int status);

/**
 * Main function of worker thread.
 *
 * @param arg thread argument.
 */
void pc__worker(void *arg);

/**
 * Callback for default message parse event.
 *
 * @param client client instance.
 * @param data   message data in bytes.
 * @param len    length of data
 */
pc_msg_t *pc__default_msg_parse_cb(pc_client_t *client,
    const char *data, size_t len);

/**
 * Callback for default message parse done event.
 *
 * @param client client instance.
 * @param msg    message parsed result created before.
 */
void pc__default_msg_parse_done_cb(pc_client_t *client, pc_msg_t *msg);

/**
 * Callback for default message encode event.
 *
 * @param  client client instance.
 * @param  reqId  request id, positive for request or 0 for notify.
 * @param  route  route string.
 * @param  msg    message object.
 * @return        encode result or buf.len = -1 for error.
 */
pc_buf_t pc__default_msg_encode_cb(pc_client_t *client, uint32_t reqId,
    const char *route, json_t *msg);

/**
 * Callback for default message encode done event.
 *
 * @param client client instance.
 * @param buf    encode result created before.
 */
void pc__default_msg_encode_done_cb(pc_client_t * client, pc_buf_t buf);

/**
 * Callback for new package arrived event.
 *
 * @param type   package type.
 * @param data   data of package body in bytes.
 * @param len    length of data.
 * @param attach attach pointer.
 */
void pc__pkg_cb(pc_pkg_type type, const char *data, size_t len,
                       void *attach);

/**
 * Clear the client instance.
 *
 * @param client client instance.
 */
void pc__client_clear(pc_client_t *client);

#endif /* PC_INTERNAL_H */