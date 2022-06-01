/*
 * TouchstoNet-Client.h
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

#ifndef SRC_TOUCHSTONET_CLIENT_H_
#define SRC_TOUCHSTONET_CLIENT_H_

#include "TouchstoNet-Settings.h"
#include "TouchstoNet-Socket-Address.h"
#include "TouchstoNet-Socket-Connection.h"
#include "TouchstoNet-Time-Counter.h"

#include <stdbool.h>

#define CLIENT_MESSAGES_BUFFER_SIZE 1024

struct TouchstoNetClient {

  /*public*/
  bool(*inject_settings_to_client)(struct TouchstoNetClient* this, struct TouchstoNetSettings* tnet_settings_to_injected);
  bool(*start_client)(struct TouchstoNetClient* this);
  bool(*stop_client)(struct TouchstoNetClient* this);

  /*private*/
  struct TouchstoNetSettings* tnet_settings_;
  struct TouchstoNetSocketConnection tnet_socket_connection_;
  struct TouchstoNetSocketAddress tnet_scoket_address_;
  struct TouchstoNetTimeCounter tnet_time_counter_;

  char* messages_buffer [CLIENT_MESSAGES_BUFFER_SIZE];
};

extern const struct TouchstoNetClientClass {
  struct TouchstoNetClient(*new)();
} TouchstoNetClient;



#endif /* SRC_TOUCHSTONET_CLIENT_H_ */
