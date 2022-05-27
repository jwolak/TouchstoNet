/*
 * TouchstoNet-Server.h
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

#ifndef SRC_TOUCHSTONET_SERVER_H_
#define SRC_TOUCHSTONET_SERVER_H_

#include "TouchstoNet-Settings.h"
#include "TouchstoNet-Socket-Address.h"
#include "TouchstoNet-Socket-Connection.h"

#include <stdbool.h>

struct TouchstoNetServer {

  /*public*/
  bool(*inject_settings_to_server)(struct TouchstoNetServer* this, struct TouchstoNetSettings* tnet_settings_to_injected);
  bool(*start_server)(struct TouchstoNetServer* this);
  bool(*stop_server)(struct TouchstoNetServer* this);

  /*private*/
  struct TouchstoNetSettings* tnet_settings_;
  struct TouchstoNetSocketAddress tnet_scoket_address_;
  struct TouchstoNetSocketConnection tnet_socket_connection_;
};

extern const struct TouchstoNetServerClass {
  struct TouchstoNetServer(*new)();
} TouchstoNetServer;



#endif /* SRC_TOUCHSTONET_SERVER_H_ */
