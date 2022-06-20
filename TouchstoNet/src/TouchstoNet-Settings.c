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

#include "TouchstoNet-Message-Model.h"

#include "LoggerC.h"

#include <arpa/inet.h>
#include <string.h>

#define TNET_MAX_PORT_NUMBER          65535
#define TNET_MIN_PORT_NUMBER          1
#define TNET_MAX_TEST_DURATION        3600
#define TNET_MIN_TEST_DURATION        1

#define TNET_DAFULT_ROLE              CLIENT
#define TNET_DEFAULT_PORT_NUM         1025
#define TNET_DEFAULT_MSG_SIZE         128
#define TNET_TEST_DURATION            0


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

int32_t get_msg_bytes_length(struct TouchstoNetSettings* this) {

  return this->msg_bytes_length_;
}

bool set_role (struct TouchstoNetSettings* this, enum tnet_role role_to_set) {

  if (role_to_set > SERVER || role_to_set < CLIENT) {

    LOG_ERROR("%s", "Invalid role provided");
    return false;
  }

  this->role_ = role_to_set;

  LOG_DEBUG("%s%s", "Role set to: ", role_to_set ? "server" : "client");
  return true;
}

bool set_port_number (struct TouchstoNetSettings* this, int32_t port_no_to_set) {

  if (port_no_to_set < TNET_MIN_PORT_NUMBER || port_no_to_set > TNET_MAX_PORT_NUMBER) {

    LOG_ERROR("%s%d", "Invalid port number: ", port_no_to_set);
    return false;
  }

  this->port_number_ = port_no_to_set;

  LOG_DEBUG("%s%d", "port number set to: ", port_no_to_set);
  return true;
}

bool set_ip_address (struct TouchstoNetSettings* this, char* ip_address_to_set) {

  in_addr_t ip_address;

  if ((ip_address = inet_addr(&ip_address_to_set[1])) < 0) {

    LOG_ERROR("%s", "Invalid IP address");
    return false;
  }

  this->ip_address_ = ip_address;
  return true;
}

bool set_test_duration(struct TouchstoNetSettings *this, int32_t test_duration_to_set) {

  if (test_duration_to_set < TNET_MIN_TEST_DURATION || test_duration_to_set > TNET_MAX_TEST_DURATION) {

    LOG_ERROR("%s%d%s%d%s%d", "Invalid test duration: ", test_duration_to_set, "Minimum time is: ", TNET_MIN_TEST_DURATION, "Maximum is:",
              TNET_MAX_TEST_DURATION);
    return false;
  }

  this->test_duration_ = test_duration_to_set;
  LOG_DEBUG("%s%d%s", "Test duration set to: ", test_duration_to_set, " [s]");
  return true;
}

bool set_msg_bytes_length(struct TouchstoNetSettings* this, int32_t msg_bytes_length_to_set) {

  if (MESSAGE_MODEL_BUFFER_SIZE > msg_bytes_length_to_set || msg_bytes_length_to_set <= 0) {

    LOG_ERROR("%s", "Number of bytes to sent exceeded");
    return false;
  }

  this->msg_bytes_length_ = msg_bytes_length_to_set;

  return true;
}

static struct TouchstoNetSettings newSettings() {
  return (struct TouchstoNetSettings) {
    .get_role = &get_role,
    .get_port_number = &get_port_number,
    .get_ip_address = &get_ip_address,
    .get_test_duration = &get_test_duration,
    .get_msg_bytes_length = &get_msg_bytes_length,
    .set_role = &set_role,
    .set_port_number = &set_port_number,
    .set_ip_address = &set_ip_address,
    .set_test_duration = &set_test_duration,
    .set_msg_bytes_length = &set_msg_bytes_length,
    .role_ = TNET_DAFULT_ROLE,
    .port_number_ = TNET_DEFAULT_PORT_NUM,
    .ip_address_ = INADDR_ANY,
    .test_duration_ = TNET_TEST_DURATION,
    .msg_bytes_length_ = TNET_DEFAULT_MSG_SIZE,
  };
}
const struct TouchstoNetSettingsClass TouchstoNetSettings = { .new = &newSettings };


