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
#include <libpiksi/util.h>

#include "firmware_state.h"
#include "manage_led.h"

#define PROGRAM_NAME "piksi_leds"

#define PUB_ENDPOINT ">tcp://localhost:43021"
#define SUB_ENDPOINT ">tcp://localhost:43020"

#define DURO_EEPROM_PATH "/sys/bus/i2c/devices/eeprom"

static bool board_is_duro(void)
{
  int fd = open(DURO_EEPROM_PATH, O_RDONLY);
  char buf[6];
  read(fd, buf, 6);
  close(fd);
  return memcmp(buf, "DUROV0", 6) == 0;
}

int main(void)
{
  logging_init(PROGRAM_NAME);

  /* Prevent czmq from catching signals */
  zsys_handler_set(NULL);

  sbp_zmq_pubsub_ctx_t *ctx = sbp_zmq_pubsub_create(PUB_ENDPOINT, SUB_ENDPOINT);
  if (ctx == NULL) {
    exit(EXIT_FAILURE);
  }

  firmware_state_init(sbp_zmq_pubsub_rx_ctx_get(ctx));
  manage_led_setup(board_is_duro());

  zmq_simple_loop(sbp_zmq_pubsub_zloop_get(ctx));

  sbp_zmq_pubsub_destroy(&ctx);
  exit(EXIT_SUCCESS);
}