/*
 * TouchstoNet-Socket-Address.c
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

#include "TouchstoNet-Socket-Address.h"

#include "LoggerC.h"


bool set_address_family(struct TouchstoNetSocketAddress *this, int16_t address_family_to_set) {

  if (AF_INET != address_family_to_set) {

    LOG_DEBUG("%s", "[TouchstoNetSocketAddress] Invalid address family to be set");
    LOG_ERROR("%s", "Invalid address family to be set");
    return false;
  }

  this->socket_address_.sin_family = address_family_to_set;

  LOG_DEBUG("%s", "[TouchstoNetSocketAddress] Set address family to AF_INET");
  return true;
}

bool set_ip_port(struct TouchstoNetSocketAddress *this, uint16_t port_number_to_set) {

  this->socket_address_.sin_port = port_number_to_set;

  LOG_DEBUG("%s%d", "[TouchstoNetSocketAddress] Port number set to: ", port_number_to_set);
  return true;
}

bool set_inet_address(struct TouchstoNetSocketAddress *this, in_addr_t inet_address_to_set) {

  this->socket_address_.sin_addr.s_addr = inet_address_to_set;

  LOG_DEBUG("%s%d", "[TouchstoNetSocketAddress] IP address set to: ", inet_address_to_set);
  return true;
}

int16_t get_address_family(struct TouchstoNetSocketAddress *this) {

  return this->socket_address_.sin_family;
}

uint16_t get_ip_port(struct TouchstoNetSocketAddress *this) {

  return this->socket_address_.sin_port;
}

in_addr_t get_inet_address(struct TouchstoNetSocketAddress *this) {

  return this->socket_address_.sin_addr.s_addr;
}

struct sockaddr_in* get_socket_address(struct TouchstoNetSocketAddress *this) {

  return &this->socket_address_;
}

static struct TouchstoNetSocketAddress newSocketAddress() {
  return (struct TouchstoNetSocketAddress) {
    .set_address_family = &set_address_family,
    .set_ip_port = &set_ip_port,
    .set_inet_address = &set_inet_address,
    .get_address_family = &get_address_family,
    .get_ip_port = &get_ip_port,
    .get_inet_address = &get_inet_address,
    .get_socket_address = &get_socket_address,
  };
}

const struct TouchstoNetSocketAddressClass TouchstoNetSocketAddress = { .new = &newSocketAddress };
