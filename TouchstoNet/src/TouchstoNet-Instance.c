/*
 * TouchstoNet-Instance.c
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

#include "TouchstoNet-Instance.h"
#include "LoggerC.h"

bool start_instance(struct TouchstoNetInstance *this) {

  if (!this->tnet_settings_) {

    LOG_DEBUG("%s", "[TouchstoNetInstance] Instance's pointer to Settings is NULL");
    return false;
  }

  if (this->tnet_settings_->get_role(this->tnet_settings_) == CLIENT) {

    LOG_DEBUG("%s", "[TouchstoNetInstance] Client instance is starting...");

    if (!this->tnet_client_.inject_settings_to_client(&this->tnet_client_, this->tnet_settings_)) {

      LOG_DEBUG("%s", "[TouchstoNetInstance] Failed to inject settings to client");
      return false;
    }
    LOG_DEBUG("%s", "[TouchstoNetInstance] Inject settings to client successful");

    if (!this->tnet_client_.start_client(&this->tnet_client_)) {

      LOG_DEBUG("%s", "[TouchstoNetInstance] Failed to start client");
      LOG_ERROR("%s", "Failed to start client");
      return false;
    }
    LOG_DEBUG("%s", "[TouchstoNetInstance] Start client successful");

  } else {

    LOG_DEBUG("%s", "[TouchstoNetInstance] Server instance is starting...");

    if (!this->tnet_server_.inject_settings_to_server(&this->tnet_server_, this->tnet_settings_)) {

      LOG_DEBUG("%s", "[TouchstoNetInstance] Failed to inject settings to server");
      return false;
    }
    LOG_DEBUG("%s", "[TouchstoNetInstance] Inject settings to server successful");

    if (!this->tnet_server_.start_server(&this->tnet_server_)) {

      LOG_DEBUG("%s", "[TouchstoNetInstance] Failed to start server");
      LOG_ERROR("%s", "Failed to start server");
      return false;
    }
    LOG_DEBUG("%s", "[TouchstoNetInstance] Start server successful");
  }

  LOG_DEBUG("%s", "[TouchstoNetInstance] Instance started successfully");
  return true;
}

bool stop_instance(struct TouchstoNetInstance *this) {

  if (!this->tnet_settings_) {

    LOG_DEBUG("%s", "Instance's pointer to Settings is NULL");
    return false;
  }

  if (this->tnet_settings_->get_role(this->tnet_settings_) == CLIENT) {

    LOG_DEBUG("%s", "[TouchstoNetInstance] Client instance is stopped");

    if (!this->tnet_client_.stop_client(&this->tnet_client_)) {

      LOG_DEBUG("%s", "[TouchstoNetInstance] Failed to stop client");
      LOG_ERROR("%s", "Failed to stop client");
      return false;
    }
    LOG_DEBUG("%s", "[TouchstoNetInstance] Stop client successful");

  } else {

    if (!this->tnet_server_.stop_server(&this->tnet_server_)) {

      LOG_DEBUG("%s", "[TouchstoNetInstance] Failed to stop server");
      LOG_ERROR("%s", "Failed to stop server");
      return false;
    }
    LOG_DEBUG("%s", "[TouchstoNetInstance] Stop server successful");
  }

  LOG_DEBUG("%s", "[TouchstoNetInstance] Instance stopped successfully");
  return true;
}

bool inject_settings_to_instance(struct TouchstoNetInstance *this, struct TouchstoNetSettings *tnet_settings_to_injected) {

  if (!tnet_settings_to_injected) {

    LOG_DEBUG("%s", "[TouchstoNetInstance] Pointer to settings for TouchstoNetInstance is null");
    return false;
  }

  this->tnet_settings_ = tnet_settings_to_injected;
  LOG_DEBUG("%s", "[TouchstoNetInstance] Settings injected successfully to Instance");
  return true;
}


static struct TouchstoNetInstance newInstance() {
  return (struct TouchstoNetInstance) {
    .start_instance = &start_instance,
    .stop_instance = &stop_instance,
    .inject_settings_to_instance = &inject_settings_to_instance,
    .tnet_client_ = TouchstoNetClient.new(),
    .tnet_server_ = TouchstoNetServer.new(),
  };
}

const struct TouchstoNetInstanceClass TouchstoNetInstance = { .new = &newInstance };
