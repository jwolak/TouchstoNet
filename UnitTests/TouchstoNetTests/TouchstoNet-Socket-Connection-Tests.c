/*
 * TouchstoNet-Socket-Connection-Tests.c
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

#include "unity.h"
#include "../../TouchstoNet/src/TouchstoNet-Socket-Connection.c"
#include "../../TouchstoNet/src/TouchstoNet-Socket-Address.c"
#include "../../TouchstoNet/src/TouchstoNet-Socket.c"

#include <stdbool.h>


void* test_client_thread() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  struct TouchstoNetSocketConnection tnet_socket_connection2 = TouchstoNetSocketConnection.new();
  tnet_socket_connection2.inject_settings_to_socket_connection(&tnet_socket_connection2, &tnet_settings);
  tnet_socket_connection2.open_socket(&tnet_socket_connection2);
  struct sockaddr_in     servaddr;
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(8080);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  char *hello = "Hello Marvell";

  tnet_socket_connection2.create_client_thread(&tnet_socket_connection2, hello, strlen(hello), &servaddr);

}

void* test_server_thread() {

  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  struct TouchstoNetSocketConnection tnet_socket_connection = TouchstoNetSocketConnection.new();
  tnet_socket_connection.inject_settings_to_socket_connection(&tnet_socket_connection, &tnet_settings);
  tnet_socket_connection.open_socket(&tnet_socket_connection);

  struct sockaddr_in socket_address_to_bind;
  socket_address_to_bind.sin_family    = AF_INET;
  socket_address_to_bind.sin_addr.s_addr = INADDR_ANY;
  socket_address_to_bind.sin_port = htons(8080);

  tnet_socket_connection.bind_to_socket(&tnet_socket_connection, &socket_address_to_bind);

  struct sockaddr_in client;
  tnet_socket_connection.create_server_thread(&tnet_socket_connection, &client);
}

void start_connection() {

  pthread_t thread_id[2];
  bool stop_order = false;

  pthread_create(&thread_id[0], NULL, test_server_thread, NULL);
  pthread_create(&thread_id[1], NULL, test_client_thread, NULL);

  pthread_join(thread_id[1], NULL);
  pthread_join(thread_id[0], NULL);

}


