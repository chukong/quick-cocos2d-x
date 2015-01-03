#ifndef PC_LISTENER_H
#define PC_LISTENER_H

#include "pomelo.h"

struct pc_listener_s {
  pc_event_cb cb;
  ngx_queue_t queue;
};

/**
 * Create new listener instance.
 */
pc_listener_t *pc_listener_new();

/**
 * Init listener.
 *
 * @param  listener listener instance
 * @return          0 or -1
 */
int pc_listener_init(pc_listener_t *listener);

/**
 * Destroy listener instance.
 *
 * @param listener listener instance
 */
void pc_listener_destroy(pc_listener_t *listener);

#endif