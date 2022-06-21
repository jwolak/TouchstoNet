/*
 * TouchstoNet-Time-Counter-Tests.c
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
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "../../TouchstoNet/src/TouchstoNet-Time-Counter.c"
#include "../../TouchstoNet/src/TouchstoNet-Instance.c"
#include "../../TouchstoNet/src/TouchstoNet-Server.c"
#include "../../TouchstoNet/src/TouchstoNet-Client.c"

#include "LoggerC.h"

int32_t global_counter;

#define TEST_TIME           2
#define LONGER_TEST_TIME    14
#define COUNTER_SET_VALUE   21
#define TIMEOUT_TO_STOP     5

bool test_callback(void* tnet_instance) {

  LOG_DEBUG("%s", "Callback called");
  global_counter = COUNTER_SET_VALUE;

  return true;
}

void TimeCounterTests_set_callback_and_callback_function_is_called_after_2s_timeout() {

  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();
  struct TouchstoNetTimeCounter tnet_time_counter = TouchstoNetTimeCounter.new();
  tnet_time_counter.set_stop_callback(&tnet_time_counter, &test_callback);

  tnet_time_counter.start_timer(&tnet_time_counter, &tnet_instance, TEST_TIME);
  TEST_ASSERT_EQUAL(global_counter, COUNTER_SET_VALUE);
}

void TimeCounterTests_set_timeout_2s_and_set_time_is_elapsed() {

  time_t time_start;
  time_t time_end;
  double time_diff = 0.0;

  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();
  struct TouchstoNetTimeCounter tnet_time_counter = TouchstoNetTimeCounter.new();
  tnet_time_counter.set_stop_callback(&tnet_time_counter, &test_callback);

  time (&time_start);
  tnet_time_counter.start_timer(&tnet_time_counter, &tnet_instance, TEST_TIME);
  time (&time_end);
  time_diff = difftime (time_end, time_start);
  LOG_DEBUG("%s%d%s","Your timer counted ", (int)time_diff, " [s]" );

  TEST_ASSERT_EQUAL((int)time_diff, TEST_TIME);
}

void TimeCounterTests_set_longer_timeout_14s_and_set_time_is_elapsed() {

  time_t time_start;
  time_t time_end;
  double time_diff = 0.0;

  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();
  struct TouchstoNetTimeCounter tnet_time_counter = TouchstoNetTimeCounter.new();
  tnet_time_counter.set_stop_callback(&tnet_time_counter, &test_callback);

  time (&time_start);
  tnet_time_counter.start_timer(&tnet_time_counter, &tnet_instance, LONGER_TEST_TIME);
  time (&time_end);
  time_diff = difftime (time_end, time_start);
  LOG_DEBUG("%s%d%s","Your timer counted ", (int)time_diff, " [s]" );

  TEST_ASSERT_EQUAL((int)time_diff, LONGER_TEST_TIME);
}

void *call_stop_counter_after_5_seconds(void* tc) {

  int32_t time_counter = 0;

  while (time_counter < 5) {
    sleep(1);
    ++time_counter;
  }

  LOG_DEBUG("%s%d%s", "Timer is going to be stopped after: ", TIMEOUT_TO_STOP, " [s]");
  ((struct TouchstoNetTimeCounter*)tc)->stop_timer((struct TouchstoNetTimeCounter*)tc);
  LOG_DEBUG("%s", "Timer stopped");

}

void TimeCounterTests_start_counter_for_14_seconds_and_stop_it_after_5_seconds() {

  time_t time_start;
  time_t time_end;
  double time_diff = 0.0;
  pthread_t thread_id;

  struct TouchstoNetInstance tnet_instance = TouchstoNetInstance.new();
  struct TouchstoNetTimeCounter tnet_time_counter = TouchstoNetTimeCounter.new();
  tnet_time_counter.set_stop_callback(&tnet_time_counter, &test_callback);

  pthread_create(&thread_id, NULL, call_stop_counter_after_5_seconds, &tnet_time_counter);
  pthread_detach(thread_id);

  time (&time_start);
  tnet_time_counter.start_timer(&tnet_time_counter, &tnet_instance, LONGER_TEST_TIME);
  time (&time_end);
  time_diff = difftime (time_end, time_start);
  LOG_DEBUG("%s%d%s","Your timer counted ", (int)time_diff, " [s]" );

  TEST_ASSERT_TRUE(TIMEOUT_TO_STOP <= (int)time_diff <= TIMEOUT_TO_STOP + 1);
}


