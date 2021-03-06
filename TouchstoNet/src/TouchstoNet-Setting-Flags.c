/*
 * TouchstoNet-Setting-Flags.c
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

#include "TouchstoNet-Setting-Flags.h"

#include "LoggerC.h"

  void set_port_number_as_set(struct TouchstoNetSettingFlags *this) {

    LOG_DEBUG("%s", "[TouchstoNetSettingFlags] Port number set flag enabled");
    this->port_number_is_set_ = true;
  }

  void set_ip_address_as_set(struct TouchstoNetSettingFlags *this) {

    LOG_DEBUG("%s", "[TouchstoNetSettingFlags] IP address set flag enabled");
    this->ip_addres_is_set_ = true;
  }

  void set_test_duration_as_set(struct TouchstoNetSettingFlags *this) {

    LOG_DEBUG("%s", "[TouchstoNetSettingFlags] Test duration time set flag enabled");
    this->test_duration_is_set_ = true;
  }

  void set_msg_bytes_length_as_set(struct TouchstoNetSettingFlags *this) {

    LOG_DEBUG("%s", "[TouchstoNetSettingFlags] Message bytes length set flag enabled");
    this->msg_bytes_length_is_set_ = true;
  }

  void set_debug_mode_as_set (struct TouchstoNetSettingFlags *this) {

    LOG_DEBUG("%s", "[TouchstoNetSettingFlags] Debug mode set flag enabled");
    this->debug_mode_is_set_ = true;
  }

  bool get_port_number_status(struct TouchstoNetSettingFlags *this) {

    return this->port_number_is_set_;
  }

  bool get_ip_address_status(struct TouchstoNetSettingFlags *this) {

    return this->ip_addres_is_set_;
  }

  bool get_test_duration_status(struct TouchstoNetSettingFlags *this) {

    return this->test_duration_is_set_;
  }

  bool get_msg_bytes_length_status(struct TouchstoNetSettingFlags *this) {

    return this->msg_bytes_length_is_set_;
  }

  bool get_debug_mode_status(struct TouchstoNetSettingFlags *this) {

    return this->debug_mode_is_set_;
  }

static struct TouchstoNetSettingFlags newSettingFlags() {
  return (struct TouchstoNetSettingFlags) {
    .port_number_is_set_ = false,
    .ip_addres_is_set_ = false,
    .test_duration_is_set_ = false,
    .msg_bytes_length_is_set_ = false,
    .debug_mode_is_set_ = false,
    .set_port_number_as_set = &set_port_number_as_set,
    .set_ip_address_as_set = &set_ip_address_as_set,
    .set_test_duration_as_set = &set_test_duration_as_set,
    .set_msg_bytes_length_as_set = &set_msg_bytes_length_as_set,
    .set_debug_mode_as_set = &set_debug_mode_as_set,
    .get_port_number_status = &get_port_number_status,
    .get_ip_address_status = &get_ip_address_status,
    .get_test_duration_status = &get_test_duration_status,
    .get_msg_bytes_length_status = &get_msg_bytes_length_status,
    .get_debug_mode_status = &get_debug_mode_status,
  };
}
const struct TouchstoNetSettingFlagsClass TouchstoNetSettingFlags = { .new = &newSettingFlags };



