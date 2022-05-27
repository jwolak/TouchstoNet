/*
 * TouchstoNet-Socket-Connection.c
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

#include "TouchstoNet-Socket-Connection.h"

#include "LoggerC.h"

#include <string.h>

struct SendRecvMsgLoopArgs {
  int sock_fd;
  void *buffer;
  struct sockaddr *server_sock_addr;
  int *recv_addr_len;
};

static void *recv_msg_loop_thread(void* recv_msg_args) {

  LOG_DEBUG("%s", "Receive messages loop thread started");

  int sockfd = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->sock_fd;
  char *buffer = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->buffer;
  struct sockaddr *client_addr = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->server_sock_addr;
  int *len = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->recv_addr_len;
  int n = 0;

  while (true) {
    n = recvfrom(sockfd, (char*) buffer, MAXLINE, MSG_WAITALL, (struct sockaddr*) client_addr, len);
  }
}

static void *send_msg_loop_thread(void* send_msg_args) {

  LOG_DEBUG("%s", "Send messages loop thread started");

  int sockfd = ((struct SendRecvMsgLoopArgs*)send_msg_args)->sock_fd;
  char *buffer_to_send = ((struct SendRecvMsgLoopArgs*)send_msg_args)->buffer;
  struct sockaddr *server_addr = ((struct SendRecvMsgLoopArgs*)send_msg_args)->server_sock_addr;
  int *len = ((struct SendRecvMsgLoopArgs*)send_msg_args)->recv_addr_len;

  while (true) {
    sendto(sockfd, (const char *)buffer_to_send, strlen(buffer_to_send), MSG_CONFIRM, (const struct sockaddr *) &server_addr, *len);
  }
}

bool inject_settings_to_socket_connection(struct TouchstoNetSocketConnection *this, struct TouchstoNetSettings* tnet_settings_to_injected) {

  if (!tnet_settings_to_injected) {

    LOG_DEBUG("%s", "Pointer to settings for TouchstoNetSocketConnection is null");
    return false;
  }

  this->tnet_settings_ = tnet_settings_to_injected;

  LOG_DEBUG("%s", "Settings injected successfully to SocketConnection");
  return true;
}

bool bind_to_socket(struct TouchstoNetSocketConnection *this, struct sockaddr_in *socket_address_to_bind) {

  if (!socket_address_to_bind) {

    LOG_DEBUG("%s", "Struct sockaddr pointer for TouchstoNetSocketConnection is null");
    return false;
  }

  if ( bind(this->tnet_socket_.get_socket(&this->tnet_socket_), (const struct sockaddr*)socket_address_to_bind,
          sizeof((*socket_address_to_bind))) < 0 )
  {
      LOG_ERROR("%s", "TouchstoNetSocketConnection bind to socket failed");
      return false;
  }

  LOG_ERROR("%s", "TouchstoNetSocketConnection bind to socket successful");
  return true;
}

bool receive_msg(struct TouchstoNetSocketConnection *this, struct sockaddr *socket_address_to_recv) {

  /*create in thread*/
  pthread_t thread_id;
  int len = 0;
  struct SendRecvMsgLoopArgs send_recv_msg_loop_args;

  send_recv_msg_loop_args.sock_fd = this->tnet_socket_.get_socket(&this->tnet_socket_);
  send_recv_msg_loop_args.server_sock_addr = socket_address_to_recv;
  send_recv_msg_loop_args.buffer = &this->recv_msg_buffer_;
  send_recv_msg_loop_args.recv_addr_len = &len;

  pthread_create(&thread_id, NULL, recv_msg_loop_thread, &send_recv_msg_loop_args);
  pthread_detach(thread_id);

  return true;
}

bool send_msg(struct TouchstoNetSocketConnection *this, void *msg_to_send_buffer, struct sockaddr *socket_address_to_send) {

  /*create in thread*/

  pthread_t thread_id;
  int len = 0;
  struct SendRecvMsgLoopArgs send_recv_msg_loop_args;

  send_recv_msg_loop_args.sock_fd = this->tnet_socket_.get_socket(&this->tnet_socket_);
  send_recv_msg_loop_args.server_sock_addr = socket_address_to_send;
  send_recv_msg_loop_args.buffer = &this->recv_msg_buffer_;
  send_recv_msg_loop_args.recv_addr_len = &len;

  pthread_create(&thread_id, NULL, send_msg_loop_thread, &send_msg_loop_thread);
  pthread_detach(thread_id);
  /*pthread_join(thread_id, NULL);*/

  return true;
}


static struct TouchstoNetSocketConnection newSocketConnection() {
  return (struct TouchstoNetSocketConnection) {
    .inject_settings_to_socket_connection = &inject_settings_to_socket_connection,
    .bind_to_socket = &bind_to_socket,
    .receive_msg = &receive_msg,
    .send_msg = &send_msg,
    .tnet_socket_ = TouchstoNetSocket.new(),
    .tnet_sock_address_ = TouchstoNetSocketAddress.new(),
  };
}

const struct TouchstoNetSocketConnectionClass TouchstoNetSocketConnection = { .new = &newSocketConnection };
