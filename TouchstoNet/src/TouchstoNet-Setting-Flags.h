/*
 * TouchstoNet-Setting-Flags.h
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

#ifndef SRC_TOUCHSTONET_SETTING_FLAGS_H_
#define SRC_TOUCHSTONET_SETTING_FLAGS_H_

#include <stdbool.h>

struct TouchstoNetSettingFlags {

  /*public*/
  void(*set_port_number_as_set)(struct TouchstoNetSettingFlags *tnet_settings_flag);
  void(*set_ip_address_as_set)(struct TouchstoNetSettingFlags *tnet_settings_flag);
  void(*set_test_duration_as_set)(struct TouchstoNetSettingFlags *tnet_settings_flag);
  void(*set_msg_bytes_length_as_set)(struct TouchstoNetSettingFlags *tnet_settings_flag);
  void(*set_debug_mode_as_set)(struct TouchstoNetSettingFlags *tnet_settings_flag);

  bool(*get_port_number_status)(struct TouchstoNetSettingFlags *tnet_settings_flag);
  bool(*get_ip_address_status)(struct TouchstoNetSettingFlags *tnet_settings_flag);
  bool(*get_test_duration_status)(struct TouchstoNetSettingFlags *tnet_settings_flag);
  bool(*get_msg_bytes_length_status)(struct TouchstoNetSettingFlags *tnet_settings_flag);
  bool(*get_debug_mode_status)(struct TouchstoNetSettingFlags *tnet_settings_flag);

  /*private*/
  bool port_number_is_set_;
  bool ip_addres_is_set_;
  bool test_duration_is_set_;
  bool msg_bytes_length_is_set_;
  bool debug_mode_is_set_;
};

extern const struct TouchstoNetSettingFlagsClass {
  struct TouchstoNetSettingFlags (*new)();
} TouchstoNetSettingFlags;



#endif /* SRC_TOUCHSTONET_SETTING_FLAGS_H_ */
