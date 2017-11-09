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

#include <libpiksi/sbp_zmq_pubsub.h>
#include <libpiksi/logging.h>

#include <libsbp/observation.h>

static u8 base_obs_counter;

static void sbp_msg_obs_callback(u16 sender_id, u8 len, u8 msg[], void *ctx)
{
  base_obs_counter++;
}

u8 firmware_state_obs_counter_get(void)
{
  return base_obs_counter;
}

void firmware_state_init(sbp_zmq_rx_ctx_t *ctx)
{
  sbp_zmq_rx_callback_register(ctx, SBP_MSG_OBS,
                               sbp_msg_obs_callback, NULL, NULL);
}
