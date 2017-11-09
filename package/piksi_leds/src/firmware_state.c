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
#include <libsbp/navigation.h>
#include <libsbp/system.h>

enum mode {
  MODE_INVALID,
  MODE_SPP,
  MODE_DGNSS,
  MODE_FLOAT,
  MODE_FIXED,
};

static u8 base_obs_counter;
static struct {
  struct {
    struct timespec systime;
    enum mode mode;
  } dgnss;
  struct {
    struct timespec systime;
    enum mode mode;
  } spp;
  bool antenna;
} soln_state;

static void sbp_msg_obs_callback(u16 sender_id, u8 len, u8 msg[], void *ctx)
{
  base_obs_counter++;
}

u8 firmware_state_obs_counter_get(void)
{
  return base_obs_counter;
}

static void sbp_msg_pos_ecef_callback(u16 sender_id, u8 len, u8 msg_[], void *ctx)
{
  msg_pos_ecef_t *msg = (void*)msg_;
  clock_gettime(CLOCK_MONOTONIC, &soln_state.spp.systime);
  soln_state.spp.mode = msg->flags & 7;
}

static void sbp_msg_baseline_ecef_callback(u16 sender_id, u8 len, u8 msg_[], void *ctx)
{
  msg_baseline_ecef_t *msg = (void*)msg_;
  clock_gettime(CLOCK_MONOTONIC, &soln_state.dgnss.systime);
  soln_state.dgnss.mode = msg->flags & 7;
}

static void sbp_msg_heartbeat_callback(u16 sender_id, u8 len, u8 msg_[], void *ctx)
{
  msg_heartbeat_t *msg = (void*)msg_;
  soln_state.antenna = msg->flags >> 31;
}

void firmware_state_init(sbp_zmq_rx_ctx_t *ctx)
{
  sbp_zmq_rx_callback_register(ctx, SBP_MSG_OBS,
                               sbp_msg_obs_callback, NULL, NULL);
  sbp_zmq_rx_callback_register(ctx, SBP_MSG_POS_ECEF,
                               sbp_msg_pos_ecef_callback, NULL, NULL);
  sbp_zmq_rx_callback_register(ctx, SBP_MSG_BASELINE_ECEF,
                               sbp_msg_baseline_ecef_callback, NULL, NULL);
  sbp_zmq_rx_callback_register(ctx, SBP_MSG_HEARTBEAT,
                               sbp_msg_heartbeat_callback, NULL, NULL);
}
