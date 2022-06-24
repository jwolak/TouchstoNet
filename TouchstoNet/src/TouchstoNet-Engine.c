/*
 * TouchstoNet-Engine.c
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

#include "TouchstoNet-Engine.h"
#include "TouchstoNet-Info-And-Graphics.h"
#include "LoggerC.h"

bool start(struct TouchstoNetEngine* this, int32_t argc, char **argv) {

  LOG_DEBUG("%s", "[TouchstoNetEngine] NetEngine is starting...");

  if (!this->tnet_parser_.inject_settings_to_args_parser(&this->tnet_parser_, &this->tnet_settings_)) {

    LOG_DEBUG("%s", "[TouchstoNetEngine] Settings injection to arguments parser failed");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetEngine] Settings injection to arguments parser is successful");

  if (!this->tnet_parser_.parse_arguments(&this->tnet_parser_, argc, argv)) {

    LOG_DEBUG("%s", "[TouchstoNetEngine] Failed to parse command line arguments");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetEngine] Parse command line arguments successful");

  printf("%s\n\n", logo_buffer);
  printf("%s\n", copyrights_buffer);

  if (!this->tnet_intsnace_.inject_settings_to_instance(&this->tnet_intsnace_,  &this->tnet_settings_)) {

    LOG_DEBUG("%s", "[TouchstoNetEngine] Settings injection to TouchstoNet instance failed");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetEngine] Settings injection to TouchstoNet instance is successful");

  if (!this->tnet_intsnace_.start_instance(&this->tnet_intsnace_)) {

    LOG_DEBUG("%s", "[TouchstoNetEngine] Failed to start TouchstoNet test instance");
    LOG_ERROR("%s", "Failed to start TouchstoNet test instance");
    return false;
  }

  LOG_DEBUG("%s", "[TouchstoNetEngine] Start TouchstoNet engine successful");
  return true;
}

bool stop(struct TouchstoNetEngine* this) {

  if (!this->tnet_intsnace_.stop_instance(&this->tnet_intsnace_)) {

    LOG_DEBUG("%s", "[TouchstoNetEngine] Stop TouchstoNet engine failed");
    LOG_ERROR("%s", "Stop TouchstoNet engine failed");
    return false;
  }

  LOG_DEBUG("%s", "[TouchstoNetEngine] Stop TouchstoNet engine successful");
  return true;
}

static struct TouchstoNetEngine newEngine() {
  return (struct TouchstoNetEngine) {
    .start = &start,
    .stop = &stop,
    .tnet_settings_ = TouchstoNetSettings.new(),
    .tnet_parser_ = TouchstoNetAgrumentsParser.new(),
    .tnet_intsnace_ = TouchstoNetInstance.new(),
  };
}
const struct TouchstoNetEngineClass TouchstoNetEngine = { .new = &newEngine };
