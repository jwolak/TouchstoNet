/*
 * TouchstoNet-Settings.c
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

#include "TouchstoNet-Settings.h"

#include "LoggerC.h"


enum tnet_role get_role(struct TouchstoNetSettings* this) {

  return this->role_;
}

int32_t get_port_number (struct TouchstoNetSettings* this) {

  return this->port_number_;
}

in_addr_t get_ip_address (struct TouchstoNetSettings* this) {

  return this->ip_address_;
}

int32_t get_test_duration (struct TouchstoNetSettings* this) {

  return this->test_duration_;
}

void set_role (struct TouchstoNetSettings* this, enum tnet_role role_to_set) {

  LOG_DEBUG("%s%s", "Role set to: ", role_to_set ? "server" : "client");
  this->role_ = role_to_set;
}

void set_port_number (struct TouchstoNetSettings* this, int32_t port_no_to_set) {

  LOG_DEBUG("%s%d", "port number set to: ", port_no_to_set);
  this->port_number_ = port_no_to_set;
}

void set_ip_address (struct TouchstoNetSettings* this, in_addr_t ip_address_to_set) {

  this->ip_address_ = ip_address_to_set;
}

void set_test_duration (struct TouchstoNetSettings* this, int32_t test_duration_to_set) {

  LOG_DEBUG("%s%d%s", "Test duration set to: ", test_duration_to_set, " [s]");
  this->test_duration_ = test_duration_to_set;
}

static struct TouchstoNetSettings new() {
  return (struct TouchstoNetSettings) {
    .get_role = &get_role,
    .get_port_number = &get_port_number,
    .get_ip_address = &get_ip_address,
    .get_test_duration = &get_test_duration,
    .set_role = &set_role,
    .set_port_number = &set_port_number,
    .set_ip_address = &set_ip_address,
    .set_test_duration = &set_test_duration
  };
}
const struct TouchstoNetSettingsClass TouchstoNetSettings = { .new = &new };


