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

#define TEST_THREAD_STOP_TIMEOUT  5

void* stop_threads(void *args) {

  int time_counter = 0;

  while (time_counter < TEST_THREAD_STOP_TIMEOUT) {

    sleep(1);
    ++time_counter;
  }

  ((struct TouchstoNetSocketConnection*)args)->stop_working_thread(((struct TouchstoNetSocketConnection*)args));
}

void* test_client_thread(void *tnet_socket_connection) {

  struct TouchstoNetSocketConnection *tnet_socket_connection_client = (struct TouchstoNetSocketConnection*)tnet_socket_connection;
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_socket_connection_client->inject_settings_to_socket_connection(tnet_socket_connection_client, &tnet_settings);
  tnet_socket_connection_client->open_socket(tnet_socket_connection_client);
  struct sockaddr_in     servaddr;
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(8080);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  char *hello = "Hello TouchstoNet";

  tnet_socket_connection_client->create_client_thread(tnet_socket_connection_client, hello, strlen(hello), &servaddr);

}

void* test_server_thread(void *tnet_socket_connection) {

  struct TouchstoNetSocketConnection *tnet_socket_connection_server = (struct TouchstoNetSocketConnection*)tnet_socket_connection;
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_socket_connection_server->inject_settings_to_socket_connection(tnet_socket_connection_server, &tnet_settings);
  tnet_socket_connection_server->open_socket(tnet_socket_connection_server);

  struct sockaddr_in socket_address_to_bind;
  socket_address_to_bind.sin_family    = AF_INET;
  socket_address_to_bind.sin_addr.s_addr = INADDR_ANY;
  socket_address_to_bind.sin_port = htons(8080);

  tnet_socket_connection_server->bind_to_socket(tnet_socket_connection_server, &socket_address_to_bind);

  struct sockaddr_in client;
  tnet_socket_connection_server->create_server_thread(tnet_socket_connection_server, &client);
}


void start_client_server_connection_and_stop_them_after_5s() {

  struct TouchstoNetSocketConnection tnet_socket_connection_for_client_thread = TouchstoNetSocketConnection.new();
  struct TouchstoNetSocketConnection tnet_socket_connection_for_server_thread = TouchstoNetSocketConnection.new();


  pthread_t thread_id[4];
  bool stop_order = false;

  time_t time_start;
  time_t time_end;
  double time_diff = 0.0;

  time (&time_start);
  pthread_create(&thread_id[0], NULL, test_server_thread, &tnet_socket_connection_for_server_thread);
  pthread_create(&thread_id[1], NULL, test_client_thread, &tnet_socket_connection_for_client_thread);
  pthread_create(&thread_id[2], NULL, stop_threads, &tnet_socket_connection_for_client_thread);
  pthread_create(&thread_id[3], NULL, stop_threads, &tnet_socket_connection_for_server_thread);

  pthread_join(thread_id[0], NULL);
  pthread_join(thread_id[1], NULL);
  pthread_join(thread_id[2], NULL);
  pthread_join(thread_id[3], NULL);


  time (&time_end);
  time_diff = difftime (time_end, time_start);
  LOG_DEBUG("%s%d%s","Your timer counted ", (int)time_diff, " [s]" );

  TEST_ASSERT_EQUAL((int)time_diff, TEST_THREAD_STOP_TIMEOUT);

  //pthread_exit(NULL);

}


