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

#define TIME_IN_SEC_PATTERN     1
#define TNET_MAX_TIME_PERIOD    3600 /* [s] */

static void *timer_loop_thread(void *settings) {

  int32_t seconds_counter = 0;
  int32_t time_period = ((struct ThreadLoopArgs*)settings)->period;
  bool(*callback_fun)(void* tnet_instance) = ((struct ThreadLoopArgs*)settings)->callback_arg;
  void *tnet_instance = ((struct ThreadLoopArgs*)settings)->tnet_instance_arg;

  LOG_DEBUG("%s%d%s", "[TouchstoNetTimeCounter] Timer loop thread launched for: ", time_period, " [s]");

  while (seconds_counter < time_period && !(*((struct ThreadLoopArgs*)settings)->stop_flag)) {
    /*no high resolution time needed*/
    sleep(TIME_IN_SEC_PATTERN);
    ++seconds_counter;
  }

  if (!callback_fun(tnet_instance)) {

    LOG_DEBUG("%s", "[TouchstoNetTimeCounter] Filed to call callback after time is elapsed");
    LOG_ERROR("%s", "Filed to call callback after time is elapsed");
    return false;
  }

  LOG_DEBUG("%s", "[TouchstoNetTimeCounter] Time has elapsed");
  LOG_DEBUG("%s", "[TouchstoNetTimeCounter] Timer loop thread stopped");
}

bool start_timer(struct TouchstoNetTimeCounter *this, void *tnet_instance, int32_t time_period) {

  LOG_DEBUG("%s%d\n", "[TouchstoNetTimeCounter] Time period to be set: ", time_period );

  this->thread_loop_args_.period = time_period;
  this->thread_loop_args_.stop_flag = &this->stop_timer_flag_;
  this->thread_loop_args_.callback_arg = this->timer_stop_callback;
  this->thread_loop_args_.tnet_instance_arg = tnet_instance;

  if (time_period == 0) {

    LOG_DEBUG("%s%d%s", "[TouchstoNetTimeCounter] Time period not provided or set to zero. Set maximum value: ", TNET_MAX_TIME_PERIOD, " [s]");
    LOG_WARNING("%s%d%s", "Time period not provided or set to zero. Set maximum value: ", TNET_MAX_TIME_PERIOD, " [s]");
    time_period = TNET_MAX_TIME_PERIOD;
  }

  if (pthread_create(&this->thread_id_, NULL, timer_loop_thread, &this->thread_loop_args_) != 0) {

    LOG_DEBUG("%s", "[TouchstoNetTimeCounter] Failed to launch timer_loop_thread");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetTimeCounter] Launch timer_loop_thread successful");

  if (pthread_detach(this->thread_id_) != 0) {

    LOG_DEBUG("%s", "[TouchstoNetTimeCounter] Filed to detached timer thread");
    return false;
  }

  LOG_DEBUG("%s", "[TouchstoNetTimeCounter] Detach timer thread successful");
  return true;
}

bool stop_timer(struct TouchstoNetTimeCounter *this) {

  LOG_DEBUG("%s", "[TouchstoNetTimeCounter] Time counting has been interrupted");

  this->stop_timer_flag_ = true;
  pthread_cancel(this->thread_id_);

  LOG_DEBUG("%s", "[TouchstoNetTimeCounter] Stop timer flag set to TRUE");
  return true;
}

bool set_stop_callback (struct TouchstoNetTimeCounter *this, bool(*callback)(void *tnet_instance)) {

  this->timer_stop_callback = callback;
  LOG_DEBUG("%s", "[TouchstoNetTimeCounter] Callback set successfully for TimeCounter");
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
