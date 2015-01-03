#ifndef PC_TRANSPORT_H
#define PC_TRANSPORT_H

#include "uv.h"
#include "pomelo.h"

/**
 * Trnasport is a simple wrap layer to isolate the pc_client_t from low layer
 * socket.
 */

/**
 * Create a new transport instance.
 *
 * @param  client the client instance that the new transport associated with.
 * @return        new transport instance or NULL for error.
 */
pc_transport_t *pc_transport_new(pc_client_t *client);

/**
 * Disconnect the low layer socket and release the resources of transport.
 *
 * @param transport pointer to the transport instance.
 */
void pc_transport_destroy(pc_transport_t *transport);

/**
 * Start the transport.
 *
 * @param  transport pointer to the transport.
 * @return           0 for ok or -1 for error.
 */
int pc_transport_start(pc_transport_t *transport);

/**
 * Tcp packet arrived callback.
 *
 * @param socket uv_stream_t instance.
 * @param nread  bytes read.
 * @param buf    data buffer.
 */
void pc_tp_on_tcp_read(uv_stream_t *socket, ssize_t nread, uv_buf_t buf);

#endif /* PC_TRANSPORT_H */