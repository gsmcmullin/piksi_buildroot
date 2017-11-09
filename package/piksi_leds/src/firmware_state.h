/*
 * Copyright (C) 2017 Swift Navigation Inc.
 * Contact: Gareth McMullin <gareth@swiftnav.com>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef __FIRMWARE_STATE_H
#define __FIRMWARE_STATE_H

#include <libpiksi/sbp_zmq_rx.h>

void firmware_state_init(sbp_zmq_rx_ctx_t *ctx);
u8 firmware_state_obs_counter_get(void);

#endif
