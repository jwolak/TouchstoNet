/*
 * TouchstoNet-Settings-Tests.c
 *
 *  Created on: 2022
 *      Author: Janusz Wolak
 */

/*-
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Janusz Wolak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include "unity.h"

#include "../../TouchstoNet/src/TouchstoNet-Settings.c"

#define TEST_PORT_NUMBER                        77
#define TEST_IP_ADDRESS                         254255168
#define TEST_DURATION                           100
#define TEST_INVALID_ROLE                       7
#define TEST_VALID_PORT_NUMBER                  1025
#define TEST_INVALID_MORE_THEN_MAX_PORT         70567
#define TEST_INVALID_NEGATIVE_PORT              -100
#define TEST_MAX_PORT_NUMBER                    65535
#define TEST_MIN_PORT_NUMBER                    1
#define TEST_VALID_IP_ADDRESS                   "127.0.0.1"
#define TEST_INVALID_IP_ADDRESS                 " 259.169.0.0"
#define TEST_VALID_TEST_DURATION                77
#define TEST_MAX_TEST_DURATION                  3600
#define TEST_MIN_TEST_DURATION                  1
#define TEST_INVALID_MAX_TEST_DURATION          TEST_MAX_TEST_DURATION + 1
#define TEST_INVALID_MIN_TEST_DURATION          TEST_MIN_TEST_DURATION - 1


void SettingsTests_call_settings_get_role_and_role_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.role_ = SERVER;

  TEST_ASSERT_EQUAL(SERVER, tnet_settings.get_role(&tnet_settings));
}

void SettingsTests_call_settings_get_port_number_and_port_number_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.port_number_ = TEST_PORT_NUMBER;

  TEST_ASSERT_EQUAL(TEST_PORT_NUMBER, tnet_settings.get_port_number(&tnet_settings));
}


void SettingsTests_call_settings_get_ip_address_and_ip_address_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.ip_address_ = TEST_IP_ADDRESS;

  TEST_ASSERT_EQUAL(TEST_IP_ADDRESS, tnet_settings.get_ip_address(&tnet_settings));
}

void SettingsTests_call_settings_get_test_duration_and_test_duration_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.test_duration_ = TEST_DURATION;

  TEST_ASSERT_EQUAL(TEST_DURATION, tnet_settings.get_test_duration(&tnet_settings));
}

void SettingsTests_call_set_role_with_server_mode_and_server_mode_is_set() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.set_role(&tnet_settings, SERVER);

  TEST_ASSERT_EQUAL(tnet_settings.role_, SERVER);
}

void SettingsTests_call_set_role_with_server_mode_and_true_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_TRUE(tnet_settings.set_role(&tnet_settings, SERVER));
}

void SettingsTests_call_set_role_with_client_mode_and_server_mode_is_set() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.set_role(&tnet_settings, CLIENT);

  TEST_ASSERT_EQUAL(tnet_settings.role_, CLIENT);
}

void SettingsTests_call_set_role_with_client_mode_and_true_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_TRUE(tnet_settings.set_role(&tnet_settings, CLIENT));
}

void SettingsTests_try_call_set_role_with_invalid_mode_and_false_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_FALSE(tnet_settings.set_role(&tnet_settings, TEST_INVALID_ROLE));
}

void SettingsTests_call_set_port_number_and_port_number_is_set() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.set_port_number(&tnet_settings, TEST_VALID_PORT_NUMBER);

  TEST_ASSERT_EQUAL(TEST_VALID_PORT_NUMBER, tnet_settings.port_number_);
}

void SettingsTests_call_set_port_number_and_true_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_TRUE(tnet_settings.set_port_number(&tnet_settings, TEST_VALID_PORT_NUMBER));
}

void SettingsTests_try_set_port_number_with_invalid_to_big_value_and_false_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_FALSE(tnet_settings.set_port_number(&tnet_settings, TEST_INVALID_MORE_THEN_MAX_PORT));
}

void SettingsTests_try_set_port_number_with_invalid_negative_value_and_false_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_FALSE(tnet_settings.set_port_number(&tnet_settings, TEST_INVALID_NEGATIVE_PORT));
}

void SettingsTests_call_set_port_number_with_max_value_and_port_number_is_set() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.set_port_number(&tnet_settings, TEST_MAX_PORT_NUMBER);

  TEST_ASSERT_EQUAL(TEST_MAX_PORT_NUMBER, tnet_settings.port_number_);
}

void SettingsTests_call_set_port_number_with_min_value_and_port_number_is_set() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.set_port_number(&tnet_settings, TEST_MIN_PORT_NUMBER);

  TEST_ASSERT_EQUAL(TEST_MIN_PORT_NUMBER, tnet_settings.port_number_);
}

void SettingsTests_call_set_ip_address_with_valid_address_and_true_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_TRUE(tnet_settings.set_ip_address(&tnet_settings, TEST_VALID_IP_ADDRESS));
}

void SettingsTests_call_set_ip_address_with_invalid_address_and_false_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_FALSE(tnet_settings.set_ip_address(&tnet_settings, TEST_INVALID_IP_ADDRESS));
}

void SettingsTests_call_set_test_duration_value_and_test_duration_is_set() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.set_test_duration(&tnet_settings, TEST_VALID_TEST_DURATION);

  TEST_ASSERT_EQUAL(TEST_VALID_TEST_DURATION, tnet_settings.test_duration_);
}

void SettingsTests_call_set_test_duration_value_and_true_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();

  TEST_ASSERT_TRUE(tnet_settings.set_test_duration(&tnet_settings, TEST_VALID_TEST_DURATION));
}

void SettingsTests_call_set_test_duration_with_max_value_and_max_duration_is_set() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.set_test_duration(&tnet_settings, TEST_MAX_TEST_DURATION);

  TEST_ASSERT_EQUAL(TEST_MAX_TEST_DURATION, tnet_settings.test_duration_);
}

void SettingsTests_call_set_test_duration_with_max_value_and_true_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_TRUE(tnet_settings.set_test_duration(&tnet_settings, TEST_MAX_TEST_DURATION));
}

void SettingsTests_call_set_test_duration_with_min_value_and_min_duration_is_set() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.set_test_duration(&tnet_settings, TEST_MIN_TEST_DURATION);

  TEST_ASSERT_EQUAL(TEST_MIN_TEST_DURATION, tnet_settings.test_duration_);
}

void SettingsTests_call_set_test_duration_with_min_value_and_true_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_TRUE(tnet_settings.set_test_duration(&tnet_settings, TEST_MIN_TEST_DURATION));
}

void SettingsTests_call_set_test_duration_with_invalid_max_value_and_false_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_FALSE(tnet_settings.set_test_duration(&tnet_settings, TEST_INVALID_MAX_TEST_DURATION));
}

void SettingsTests_call_set_test_duration_with_invalid_min_value_and_false_is_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  TEST_ASSERT_FALSE(tnet_settings.set_test_duration(&tnet_settings, TEST_INVALID_MIN_TEST_DURATION));
}
