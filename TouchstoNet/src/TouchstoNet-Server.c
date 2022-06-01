/*
 * TouchstoNet-Server.c
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

#include "TouchstoNet-Server.h"

#include "LoggerC.h"

bool inject_settings_to_server(struct TouchstoNetServer* this, struct TouchstoNetSettings* tnet_settings_to_injected) {

  if (!tnet_settings_to_injected) {

    LOG_DEBUG("%s", "Settings pointer for TouchstoNetServer is null");
    return false;
  }

  this->tnet_settings_ = tnet_settings_to_injected;

  LOG_DEBUG("%s", "Settings injected to TouchstoNetServer successfully");
  return true;
}

bool start_server(struct TouchstoNetServer* this) {

  if (this->tnet_socket_connection_.inject_settings_to_socket_connection(&this->tnet_socket_connection_, this->tnet_settings_)) {

    LOG_DEBUG("%s", "Setting injection to TouchstoNetSocketConnection failed");
    return false;
  }

  if (this->tnet_scoket_address_.set_address_family(&this->tnet_scoket_address_, AF_INET)) {

    LOG_DEBUG("%s", "Failed to set address family for TouchstoNetSocketAddress in TouchstoNetServer");
    return false;
  }

  if (!this->tnet_scoket_address_.set_inet_address(&this->tnet_scoket_address_, INADDR_ANY)) {

    LOG_DEBUG("%s", "Failed to set socket address for TouchstoNetSocketAddress in TouchstoNetServer");
    return false;
  }

  if (!this->tnet_scoket_address_.set_ip_port(&this->tnet_scoket_address_, this->tnet_settings_->get_port_number(this->tnet_settings_))) {

    LOG_DEBUG("%s", "Failed to set port number for TouchstoNetSocketAddress in TouchstoNetServer");
    return false;
  }

  if (!this->tnet_socket_connection_.open_socket(&this->tnet_socket_connection_)) {

    LOG_DEBUG("%s", "TouchstoNetServer: Open socket failed");
    return false;
  }

  if(!this->tnet_socket_connection_.bind_to_socket(&this->tnet_socket_connection_, this->tnet_scoket_address_.get_socket_address(&this->tnet_scoket_address_))) {

    LOG_ERROR("%s", "Server failed bind to the socket");
    return false;
  }

  if (!this->tnet_socket_connection_.create_server_thread(&this->tnet_socket_connection_, &this->tnet_scoket_address_.socket_address_)) {

    LOG_DEBUG("%s", "TouchstoNetServer: Create server thread failed");
    return false;
  }

  return true;
}

bool stop_server(struct TouchstoNetServer* this) {

  if (!this->tnet_socket_connection_.stop_working_thread(&this->tnet_socket_connection_)) {

    LOG_DEBUG("%s", "TouchstoNetServer: Stop server thread filed");
    return false;
  }

  if (!this->tnet_socket_connection_.close_connection(&this->tnet_socket_connection_)) {

    LOG_DEBUG("%s", "TouchstoNetServer: Close socket failed");
    return false;
  }

  LOG_DEBUG("%s", "TouchstoNetServer: Stop server successful");
  return true;
}

static struct TouchstoNetServer newServer() {
  return (struct TouchstoNetServer) {
    .inject_settings_to_server = &inject_settings_to_server,
    .start_server = &start_server,
    .stop_server = &stop_server,
    .tnet_scoket_address_ = TouchstoNetSocketAddress.new(),
    .tnet_socket_connection_ = TouchstoNetSocketConnection.new(),
  };
}

const struct TouchstoNetServerClass TouchstoNetServer = { .new = &newServer };
