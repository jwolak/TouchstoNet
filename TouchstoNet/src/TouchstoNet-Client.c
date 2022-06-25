/*
 * TouchstoNet-Client.c
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

#include "TouchstoNet-Client.h"
#include "LoggerC.h"

#include <string.h>

static bool stop_client_wrapper(void* args) {

  LOG_DEBUG("%s", "[TouchstoNetClient] stop_client_wrapper()  called")
  return ((struct TouchstoNetSocketConnection*)args)->stop_working_thread((struct TouchstoNetSocketConnection*)args);
}

bool inject_settings_to_client (struct TouchstoNetClient *this, struct TouchstoNetSettings *tnet_settings_to_injected) {

  if (!tnet_settings_to_injected) {

    LOG_DEBUG("%s", "[TouchstoNetClient] TouchstoNetClient: Settings pointer is null");
    return false;
  }

  this->tnet_settings_ = tnet_settings_to_injected;

  LOG_DEBUG("%s", "[TouchstoNetClient] Settings injected successfully");
  return true;
}

bool start_client(struct TouchstoNetClient* this) {

  if (!this->tnet_socket_connection_.inject_settings_to_socket_connection(&this->tnet_socket_connection_, this->tnet_settings_)) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Settings injection to TouchstoNetSocketConnection failed");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Settings injection to TouchstoNetSocketConnection successful");

  if (!this->tnet_scoket_address_.set_address_family(&this->tnet_scoket_address_, AF_INET)) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Failed to set address family for TouchstoNetSocketAddress");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Set address family for TouchstoNetSocketAddress in TouchstoNetServer successful");

  if (!this->tnet_scoket_address_.set_inet_address(&this->tnet_scoket_address_, this->tnet_settings_->get_ip_address(this->tnet_settings_))) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Failed to set socket address for TouchstoNetSocketAddress");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Set socket address for TouchstoNetSocketAddress in TouchstoNetServer successful");

  if (!this->tnet_scoket_address_.set_ip_port(&this->tnet_scoket_address_, this->tnet_settings_->get_port_number(this->tnet_settings_))) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Failed to set port number for TouchstoNetSocketAddress");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Set port number for TouchstoNetSocketAddress successful");

  if (!this->tnet_socket_connection_.open_socket(&this->tnet_socket_connection_)) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Open socket failed");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Open socket successful");

  if (!this->tnet_message_model_.prepare_message(&this->tnet_message_model_, this->tnet_settings_->get_msg_bytes_length(this->tnet_settings_))) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Failed to prepare massage to be send");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Prepare massage to be send successful");

  /*set callback and start timer for client*/
  if (!this->tnet_time_counter_.set_stop_callback(&this->tnet_time_counter_, &stop_client_wrapper)) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Failed to set time counter callback");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Set time counter callback successful");

  if (!this->tnet_time_counter_.start_timer(&this->tnet_time_counter_, &this->tnet_socket_connection_, this->tnet_settings_->get_test_duration(this->tnet_settings_)) ) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Failed to start time counter");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Start time counter successful");

  if (!this->tnet_socket_connection_.create_client_thread(&this->tnet_socket_connection_, this->tnet_message_model_.get_buffer(&this->tnet_message_model_) , this->tnet_message_model_.get_msg_size(&this->tnet_message_model_), this->tnet_scoket_address_.get_socket_address(&this->tnet_scoket_address_))) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Create client thread failed");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Create client thread successful");

  LOG_DEBUG("%s", "[TouchstoNetClient] Start client successful");
  return true;
}

bool stop_client(struct TouchstoNetClient* this) {

  if (!this->tnet_socket_connection_.stop_working_thread(&this->tnet_socket_connection_)) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Stop server thread failed");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Stop server thread successful");

  if (!this->tnet_socket_connection_.close_connection(&this->tnet_socket_connection_)) {

    LOG_DEBUG("%s", "[TouchstoNetClient] Close socket failed");
    return false;
  }
  LOG_DEBUG("%s", "[TouchstoNetClient] Close socket successful");

  if (!this->tnet_time_counter_.stop_timer(&this->tnet_time_counter_)) {

    LOG_WARNING("%s", "[TouchstoNetClient] Failed to stop time counter");
  }

  LOG_DEBUG("%s", "[TouchstoNetClient] Stop client successful");
  return true;
}

static struct TouchstoNetClient newClient() {
  return (struct TouchstoNetClient) {
    .inject_settings_to_client = &inject_settings_to_client,
    .start_client = &start_client,
    .stop_client = &stop_client,
    .tnet_socket_connection_ = TouchstoNetSocketConnection.new(),
    .tnet_scoket_address_ = TouchstoNetSocketAddress.new(),
    .tnet_message_model_ = TouchstoNetMessageModel.new(),
    .tnet_time_counter_ = TouchstoNetTimeCounter.new(),
  };
}

const struct TouchstoNetClientClass TouchstoNetClient = { .new = &newClient };
