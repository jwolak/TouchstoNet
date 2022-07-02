/*
 * TouchstoNet-Socket-Connection.h
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

#ifndef SRC_TOUCHSTONET_SOCKET_CONNECTION_H_
#define SRC_TOUCHSTONET_SOCKET_CONNECTION_H_

#include "TouchstoNet-Settings.h"
#include "TouchstoNet-Socket.h"
#include "TouchstoNet-Socket-Address.h"

#include <stdbool.h>

#define MAXLINE 1024

struct TouchstoNetSocketConnection {

  /*public*/
  bool(*inject_settings_to_socket_connection)(struct TouchstoNetSocketConnection* this, struct TouchstoNetSettings* tnet_settings_to_injected);
  bool(*bind_to_socket)(struct TouchstoNetSocketConnection *this, struct sockaddr_in *socket_address_to_bind);
  bool(*open_socket)(struct TouchstoNetSocketConnection *this);
  bool(*close_connection)(struct TouchstoNetSocketConnection *this);
  bool(*create_server_thread)(struct TouchstoNetSocketConnection *this, struct sockaddr_in *socket_server_address);
  bool(*create_client_thread)(struct TouchstoNetSocketConnection *this, void *msg_to_send_buffer, int32_t msg_send_size, struct sockaddr_in *socket_client_address);
  bool(*stop_working_thread)(struct TouchstoNetSocketConnection *this);

  /*private*/
  struct TouchstoNetSettings* tnet_settings_;
  char recv_msg_buffer_[MAXLINE];
  struct TouchstoNetSocket tnet_socket_;
  struct TouchstoNetSocketAddress tnet_sock_address_;
  /* always one thread for now, so no mutex needed */
  bool stop_thread_;
  pthread_t thread_id_;
  pthread_t statistic_thread_id_;
  size_t sent_pkts_counter_;
  int32_t real_test_time_;
};

extern const struct TouchstoNetSocketConnectionClass {
  struct TouchstoNetSocketConnection (*new)();
} TouchstoNetSocketConnection;

#endif /* SRC_TOUCHSTONET_SOCKET_CONNECTION_H_ */
