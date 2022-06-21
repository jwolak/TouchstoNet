/*
 * TouchstoNet-Instance-Tests.c
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

/*Do not include!*/
/*#include "../../TouchstoNet/src/TouchstoNet-Instance.c" - already included in: TouchstoNet-Time-Counter-Tests.c*/

#define TEST_PORT_NUMBER 77
#define UNKNOWN_ROLE     7

void InstanceTests_inject_settings_to_instance_with_value_and_the_value_in_instance_is_the_same() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();

  tnet_settings.port_number_ = TEST_PORT_NUMBER;
  tnet_instance.inject_settings_to_instance(&tnet_instance, &tnet_settings);

  TEST_ASSERT_EQUAL(TEST_PORT_NUMBER, tnet_instance.tnet_settings_->port_number_);
}

void InstanceTests_inject_settings_to_instance_and_it_is_successful_and_true_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();

  TEST_ASSERT_TRUE(tnet_instance.inject_settings_to_instance(&tnet_instance, &tnet_settings));
}

void InstanceTests_try_inject_null_pointer_of_settings_to_instance_and_false_returned() {

  struct TouchstoNetSettings* tnet_settings = NULL;
  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();

  TEST_ASSERT_FALSE(tnet_instance.inject_settings_to_instance(&tnet_instance, tnet_settings));
}

void InstanceTests_try_to_start_instance_with_null_pointer_of_settings_to_instance_and_false_returned() {

  struct TouchstoNetSettings* tnet_settings = NULL;
  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();

  TEST_ASSERT_FALSE(tnet_instance.start_instance(&tnet_instance));
}

void InstanceTests_try_to_start_instance_without_injeted_settings_and_false_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();

  TEST_ASSERT_FALSE(tnet_instance.start_instance(&tnet_instance));
}

void InstanceTests_start_instance_in_client_mode_and_it_is_successful_then_true_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();

  tnet_settings.role_ = CLIENT;
  tnet_instance.inject_settings_to_instance(&tnet_instance, &tnet_settings);

  TEST_ASSERT_TRUE(tnet_instance.start_instance(&tnet_instance));
}

void InstanceTests_start_instance_in_server_mode_and_it_is_successful_then_true_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();

  tnet_settings.role_ = SERVER;
  tnet_instance.inject_settings_to_instance(&tnet_instance, &tnet_settings);

  TEST_ASSERT_TRUE(tnet_instance.start_instance(&tnet_instance));
}


void InstanceTests_stop_instance_in_client_mode_and_it_is_successful_then_true_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();

  tnet_settings.role_ = CLIENT;
  tnet_instance.inject_settings_to_instance(&tnet_instance, &tnet_settings);

  TEST_ASSERT_TRUE(tnet_instance.stop_instance(&tnet_instance));
}

void InstanceTests_stop_instance_in_server_mode_and_it_is_successful_then_true_returned() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();

  tnet_settings.role_ = SERVER;
  tnet_instance.inject_settings_to_instance(&tnet_instance, &tnet_settings);

  TEST_ASSERT_TRUE(tnet_instance.stop_instance(&tnet_instance));
}

