/*
 * TouchstoNet-Time-Counter.c
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

#include "TouchstoNet-Time-Counter.h"
#include "LoggerC.h"

#include <unistd.h>
#include <stdbool.h>

#define TIME_IN_SEC_PATTERN 1

struct ThreadLoopArgs {
  int32_t period;
  bool *stop_flag;
};

static void *timer_loop_thread(void* settings) {

  int32_t seconds_counter = 0;
  int32_t time_period = ((struct ThreadLoopArgs*)settings)->period;

  LOG_DEBUG("%s%d%s", "Timer loop thread launched for: ", time_period, " [s]");

  while (seconds_counter < time_period && !(*((struct ThreadLoopArgs*)settings)->stop_flag)) {
    /*no high resolution time needed*/
    sleep(TIME_IN_SEC_PATTERN);
    ++seconds_counter;
  }

  LOG_DEBUG("%s", "Timer loop thread stopped");
}

bool start_timer(struct TouchstoNetTimeCounter *this, void* tnet_instance, int32_t time_period) {

  struct ThreadLoopArgs thread_loop_args;
  thread_loop_args.period = time_period;
  thread_loop_args.stop_flag = &this->stop_timer_flag_;

  if (pthread_create(&this->thread_id_, NULL, timer_loop_thread, &thread_loop_args) != 0) {

    LOG_DEBUG("%s", "TouchstoNetTimeCounter: Failed to launch timer_loop_thread");
    return false;
  }

  pthread_join(this->thread_id_, NULL);

  if (!this->timer_stop_callback(tnet_instance)) {

    LOG_ERROR("%s", "Filed to call callback after time is elapsed");
    return false;
  }

  LOG_DEBUG("%s", "Time has elapsed");
  return true;
}

bool stop_timer(struct TouchstoNetTimeCounter *this) {

  LOG_DEBUG("%s", "Time counting has been interrupted");

  this->stop_timer_flag_ = true;
  pthread_cancel(this->thread_id_);

  return true;
}

bool set_stop_callback (struct TouchstoNetTimeCounter* this, bool(*callback)(void* tnet_instance)) {

  this->timer_stop_callback = callback;
  LOG_DEBUG("%s", "Callback set successfully for TimeCounter");
  return true;
}


static struct TouchstoNetTimeCounter newTimeCounter() {
  return (struct TouchstoNetTimeCounter) {
    .start_timer = &start_timer,
    .stop_timer = &stop_timer,
    .set_stop_callback = &set_stop_callback,
    .stop_timer_flag_ = false,
  };
}

const struct TouchstoNetTimeCounterClass TouchstoNetTimeCounter = { .new = &newTimeCounter };
