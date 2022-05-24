/*
 * TouchstoNet-Settings.h
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

#ifndef SRC_TOUCHSTONET_SETTINGS_H_
#define SRC_TOUCHSTONET_SETTINGS_H_

#include <stdbool.h>
#include <stdint.h>

#include <netinet/in.h>

enum tnet_role {
  CLIENT = 0,
  SERVER = 1
};

struct TouchstoNetSettings {

  /*public*/
  enum tnet_role(*get_role)(struct TouchstoNetSettings* this);
  int32_t(*get_port_number)(struct TouchstoNetSettings* this);
  in_addr_t(*get_ip_address)(struct TouchstoNetSettings* this);
  int32_t(*get_test_duration)(struct TouchstoNetSettings* this);

  void(*set_role)(struct TouchstoNetSettings* this, enum tnet_role role_to_set);
  void(*set_port_number)(struct TouchstoNetSettings* this, int32_t port_no_to_set);
  void(*set_ip_address)(struct TouchstoNetSettings* this, in_addr_t ip_address_to_set);
  void(*set_test_duration)(struct TouchstoNetSettings* this, int32_t test_duration_to_set);

 /* private*/
  enum tnet_role role_;
  int32_t        port_number_;
  in_addr_t      ip_address_;
  int32_t        test_duration_;
};

extern const struct TouchstoNetSettingsClass {
  struct TouchstoNetSettings (*new)();
} TouchstoNetSettings;

#endif /* SRC_TOUCHSTONET_SETTINGS_H_ */
