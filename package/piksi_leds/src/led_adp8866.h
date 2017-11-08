/*
 * Copyright (C) 2016 Swift Navigation Inc.
 * Contact: Jacob McNamee <jacob@swiftnav.com>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef SWIFTNAV_LED_ADP8866_H
#define SWIFTNAV_LED_ADP8866_H

#include <libswiftnav/common.h>

#define LED_ADP8866_LED_COUNT 9
#define LED_ADP8866_BRIGHTNESS_MAX 127

typedef struct {
  u8 led;
  u8 brightness;
} led_adp8866_led_state_t;

void led_adp8866_init(void);

bool led_adp8866_led_set(const led_adp8866_led_state_t *led_state);
bool led_adp8866_leds_set(const led_adp8866_led_state_t *led_states,
                          u32 led_states_count);

#endif /* SWIFTNAV_LED_ADP8866_H */
