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
#include "TouchstoNet-Message-Model.h"

#include "LoggerC.h"

#include <string.h>
#include <signal.h>

struct SendRecvMsgLoopArgs {
  int sock_fd;
  void *buffer;
  int32_t buffer_size;
  struct sockaddr_in *server_sock_addr;
  int *recv_addr_len;
  bool *interrrupt_thread;
};

static void *server_recv_and_reply_msg_loop_thread(void *recv_msg_args) {

  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Receive messages loop thread started");

  char recived_msg_buffer[MESSAGE_MODEL_BUFFER_SIZE];

  int sockfd = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->sock_fd;
  struct sockaddr_in *client_addr = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->server_sock_addr;
  int *len = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->recv_addr_len;
  bool *stop_thread_flag = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->interrrupt_thread;
  int n = 0;
  ssize_t no_of_recv_msgs_by_server = 0;
  ssize_t no_of_sent_msgs_by_server = 0;

  *len = sizeof(client_addr);
  while(!(*stop_thread_flag)) {
    no_of_recv_msgs_by_server = recvfrom(sockfd, (char*) recived_msg_buffer, MESSAGE_MODEL_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*) client_addr, len);
    no_of_sent_msgs_by_server = sendto(sockfd, (const char *)recived_msg_buffer, strlen(recived_msg_buffer),  MSG_CONFIRM, (const struct sockaddr *) client_addr, *len);
  }
}

static void *client_send_and_recv_msg_loop_thread(void *send_msg_args) {

  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Send messages loop thread started");

  char recived_msg_buffer[MESSAGE_MODEL_BUFFER_SIZE];

  int sockfd = ((struct SendRecvMsgLoopArgs*)send_msg_args)->sock_fd;
  char *buffer_to_send = ((struct SendRecvMsgLoopArgs*)send_msg_args)->buffer;
  int32_t buffer_to_send_size = ((struct SendRecvMsgLoopArgs*)send_msg_args)->buffer_size;
  struct sockaddr_in *server_addr = ((struct SendRecvMsgLoopArgs*)send_msg_args)->server_sock_addr;
  bool *stop_thread_flag = ((struct SendRecvMsgLoopArgs*)send_msg_args)->interrrupt_thread;
  int *len = ((struct SendRecvMsgLoopArgs*)send_msg_args)->recv_addr_len;
  ssize_t no_of_recv_msgs_by_client = 0;
  ssize_t no_of_sent_msgs_by_client = 0;

  while (!(*stop_thread_flag)) {
    no_of_sent_msgs_by_client = sendto(sockfd, (const char *)buffer_to_send, buffer_to_send_size, MSG_CONFIRM, (const struct sockaddr *) server_addr, sizeof(*server_addr)/**len*/);
    no_of_sent_msgs_by_client = recvfrom(sockfd, (char *)recived_msg_buffer, MAXLINE,  MSG_WAITALL, (struct sockaddr *) server_addr, len);
  }
}

bool inject_settings_to_socket_connection(struct TouchstoNetSocketConnection *this, struct TouchstoNetSettings *tnet_settings_to_injected) {

  if (!tnet_settings_to_injected) {

    LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Pointer to settings is null");
    return false;
  }

  this->tnet_settings_ = tnet_settings_to_injected;

  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Settings injected successfully");
  return true;
}

bool bind_to_socket(struct TouchstoNetSocketConnection *this, struct sockaddr_in *socket_address_to_bind) {

  if (!socket_address_to_bind) {

    LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Struct sockaddr pointer is null");
    return false;
  }

  if ( bind(this->tnet_socket_.get_socket(&this->tnet_socket_), (const struct sockaddr*)socket_address_to_bind,
          sizeof((*socket_address_to_bind))) < 0 )
  {
      LOG_DEBUG("%s", "[TouchstoNetSocketConnection] bind to socket failed");
      LOG_ERROR("%s", "Bind to socket failed");
      return false;
  }

  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Bind to socket successful");
  return true;
}

bool open_socket (struct TouchstoNetSocketConnection *this) {

  if (!this->tnet_socket_.create_udp(&this->tnet_socket_)) {

    LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Failed to open UDP socket");
    return false;
  }

  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Open UDP socket successful");
  return true;
}

bool close_connection(struct TouchstoNetSocketConnection *this) {

  if (!this->tnet_socket_.close_socket(&this->tnet_socket_)) {

    LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Close socket failed");
    return false;
  }

  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Close socket successful");
  return true;
}

bool create_server_thread(struct TouchstoNetSocketConnection *this, struct sockaddr_in *socket_server_address) {

  /*create in thread*/
  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] receive_msg() launched");

  int len = 0;
  struct SendRecvMsgLoopArgs send_recv_msg_loop_args;
  this->stop_thread_ = false;

  send_recv_msg_loop_args.sock_fd = this->tnet_socket_.get_socket(&this->tnet_socket_);
  send_recv_msg_loop_args.server_sock_addr = socket_server_address;
  send_recv_msg_loop_args.buffer = &this->recv_msg_buffer_;
  send_recv_msg_loop_args.recv_addr_len = &len;
  send_recv_msg_loop_args.interrrupt_thread = &this->stop_thread_;

  if (pthread_create(&this->thread_id_, NULL, server_recv_and_reply_msg_loop_thread, &send_recv_msg_loop_args) != 0) {

    LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Failed to launch server_recv_and_reply_msg_loop_thread");
    return false;
  }
  LOG_DEBUG("%s%ld%s", "[TouchstoNetSocketConnection] Thread id of server_recv_and_reply_msg_loop_thread: [",this->thread_id_, "]")
  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Launched server_recv_and_reply_msg_loop_thread successfully");

  pthread_join(this->thread_id_, NULL);

  return true;
}

bool create_client_thread(struct TouchstoNetSocketConnection *this, void *msg_to_send_buffer, int32_t msg_send_size, struct sockaddr_in *socket_client_address) {

  /*create in thread*/
  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] send_msg() is launched");

  int len = 0;
  struct SendRecvMsgLoopArgs send_recv_msg_loop_args;
  this->stop_thread_ = false;

  send_recv_msg_loop_args.sock_fd = this->tnet_socket_.get_socket(&this->tnet_socket_);
  send_recv_msg_loop_args.server_sock_addr = socket_client_address;
  send_recv_msg_loop_args.buffer = msg_to_send_buffer;
  send_recv_msg_loop_args.buffer_size = msg_send_size;
  send_recv_msg_loop_args.recv_addr_len = &len;
  send_recv_msg_loop_args.interrrupt_thread = &this->stop_thread_;

  if(pthread_create(&this->thread_id_, NULL, client_send_and_recv_msg_loop_thread, &send_recv_msg_loop_args) != 0){

    LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Failed to launch client_send_and_recv_msg_loop_thread");
    return false;
  }
  LOG_DEBUG("%s%ld%s", "[TouchstoNetSocketConnection] Thread id of client_send_and_recv_msg_loop_thread: [",this->thread_id_, "]");
  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Launched client_send_and_recv_msg_loop_thread successfully");

  pthread_join(this->thread_id_, NULL);

  return true;
}

bool stop_working_thread(struct TouchstoNetSocketConnection *this) {

  this->stop_thread_ = true;
  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Working thread has been stopped");
  pthread_cancel(this->thread_id_);

  LOG_DEBUG("%s%ld%s", "[TouchstoNetSocketConnection] Thread: [",this->thread_id_, "] has been cancelled");
  return true;
}

static struct TouchstoNetSocketConnection newSocketConnection() {
  return (struct TouchstoNetSocketConnection) {
    .inject_settings_to_socket_connection = &inject_settings_to_socket_connection,
    .bind_to_socket = &bind_to_socket,
    .open_socket = &open_socket,
    .close_connection = &close_connection,
    .create_server_thread = &create_server_thread,
    .create_client_thread = &create_client_thread,
    .stop_working_thread = &stop_working_thread,
    .tnet_socket_ = TouchstoNetSocket.new(),
    .tnet_sock_address_ = TouchstoNetSocketAddress.new(),
  };
}

const struct TouchstoNetSocketConnectionClass TouchstoNetSocketConnection = { .new = &newSocketConnection };
