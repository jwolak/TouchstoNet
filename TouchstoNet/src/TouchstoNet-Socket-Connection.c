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
#include <unistd.h>
#include <stdio.h>

#include <arpa/inet.h>

#define ONE_KILO  1024

struct SendRecvMsgLoopArgs {
  int sock_fd;
  void *buffer;
  int32_t buffer_size;
  struct sockaddr_in *server_sock_addr;
  int *recv_addr_len;
  bool *interrrupt_thread;
  size_t *amount_of_packets_sent_by_client;
  int32_t msg_size;
  int32_t* real_test_time;
};

static void print_summary(struct TouchstoNetSocketConnection *this) {

  char text_address_buffer[INET_ADDRSTRLEN];
  int32_t real_test_time = this->real_test_time_;
  size_t total_packets_sent = this->sent_pkts_counter_;
  in_addr_t server_ip_address = this->tnet_settings_->get_ip_address(this->tnet_settings_);
  size_t total_packets_sent_in_kilo = (size_t)(this->sent_pkts_counter_ / ONE_KILO);
  size_t pkts_per_second_ratio = (size_t)(this->sent_pkts_counter_ / real_test_time);
  size_t pkts_per_second_ratio_in_kilo = (size_t)((this->sent_pkts_counter_ / real_test_time) / ONE_KILO);
  int32_t packet_size = this->tnet_settings_->get_msg_bytes_length(this->tnet_settings_);
  size_t sent_bytes_ratio = (size_t)(this->sent_pkts_counter_ * this->tnet_settings_->get_msg_bytes_length(this->tnet_settings_));
  size_t sent_bytes_ratio_in_kilo = (size_t)((this->sent_pkts_counter_ * this->tnet_settings_->get_msg_bytes_length(this->tnet_settings_) / ONE_KILO));
  size_t sent_bytes_ratio_in_mega = (size_t)(((this->sent_pkts_counter_ * this->tnet_settings_->get_msg_bytes_length(this->tnet_settings_) / ONE_KILO)) / ONE_KILO);
  size_t bytes_per_second_ratio = (size_t)((this->sent_pkts_counter_ * this->tnet_settings_->get_msg_bytes_length(this->tnet_settings_)) / real_test_time);
  size_t bytes_per_second_ratio_in_kilo = (size_t)(((this->sent_pkts_counter_ * this->tnet_settings_->get_msg_bytes_length(this->tnet_settings_)) / real_test_time) / ONE_KILO);
  size_t bytes_per_second_ratio_in_mega = (size_t)((((this->sent_pkts_counter_ * this->tnet_settings_->get_msg_bytes_length(this->tnet_settings_)) / real_test_time) / ONE_KILO) / ONE_KILO);

  printf("%s", "\n\n\n");
  printf("\n\n%s\n",       "[Test summary      ]: ");
  printf("%s%24s\n",       "[Server IP         ]: ",   inet_ntop(AF_INET, &server_ip_address, text_address_buffer, INET_ADDRSTRLEN));
  printf("%s%16d%s\n",     "[Real test time    ]: ",   real_test_time,        " [s]");
  printf("%s%16d%s\n",     "[Packet size       ]: ",   packet_size,           " [B]");
  printf("%s%16zu%s\t%24zu%s%s\n",    "[Total packets sent]: ",   total_packets_sent,    " [pkts]", total_packets_sent_in_kilo, "k", " [pkts]");
  printf("%s%16zu%s\t%16zu%s%s\n",    "[Packet throughput ]: ",   pkts_per_second_ratio, " [pkts/sec]", pkts_per_second_ratio_in_kilo, "k", " [pkts/sec]" );
  printf("%s%16zu%s\t%24zu%s%s\t%24zu%s%s\n",    "[Bytes sent        ]: ",   sent_bytes_ratio,      " [Bytes]", sent_bytes_ratio_in_kilo, "k", " [Bytes]", sent_bytes_ratio_in_mega, "M", " [Bytes]");
  printf("%s%16zu%s\t%16zu%s%s\t%24zu%s%s\n",    "[Bytes throughput  ]: ",   bytes_per_second_ratio," [Bytes/sec]", bytes_per_second_ratio_in_kilo, "k", " [Bytes/sec]", bytes_per_second_ratio_in_mega, "M", " [Bytes/sec]");
  printf("%s", "\n\n");
}

void *client_statistic_thread(void *recv_msg_args) {

  bool *stop_thread_flag = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->interrrupt_thread;
  size_t *no_of_sent_msgs_by_client = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->amount_of_packets_sent_by_client;
  int32_t message_bytes_size = ((struct SendRecvMsgLoopArgs*)recv_msg_args)->msg_size;

  int count_time = 0;
  size_t bytes_throughput_per_second = 0;
  size_t packet_throughput_per_second = 0;
  size_t number_of_sent_packets = 0;

  printf("\n%s\n", "[Instant figures:]");

  while(!(*stop_thread_flag)) {

    sleep(1);
    ++count_time;
    fflush(stdout);
    bytes_throughput_per_second = (size_t)((((*no_of_sent_msgs_by_client) * message_bytes_size)/1024)/count_time);
    packet_throughput_per_second = (size_t)(((*no_of_sent_msgs_by_client)/count_time));
    number_of_sent_packets = *no_of_sent_msgs_by_client;
    *(((struct SendRecvMsgLoopArgs*)recv_msg_args)->real_test_time) = count_time;
    printf("\r "
        "%s%4d%s"
        "%zu%s"
        "%zu%s"
        "%s%zu%s",
        "Time:", count_time, " [s] "
        "  Pkts sent: ", number_of_sent_packets, " [pkts]"
        "  Pkts throughput: ", packet_throughput_per_second , " [pkts/sec]",
        "  Bytes throughput: ", bytes_throughput_per_second > ONE_KILO ? (size_t)(bytes_throughput_per_second / ONE_KILO) : bytes_throughput_per_second , bytes_throughput_per_second > ONE_KILO ? " [MB/sec]" : " [kB/sec]");
  }
}


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
  size_t *pkts_counter = ((struct SendRecvMsgLoopArgs*)send_msg_args)->amount_of_packets_sent_by_client;

  ssize_t no_of_recv_msgs_by_client = 0;
  ssize_t no_of_sent_msgs_by_client = 0;

  while (!(*stop_thread_flag)) {
    no_of_sent_msgs_by_client = sendto(sockfd, (const char *)buffer_to_send, buffer_to_send_size, MSG_CONFIRM, (const struct sockaddr *) server_addr, sizeof(*server_addr)/**len*/);
    no_of_recv_msgs_by_client = recvfrom(sockfd, (char *)recived_msg_buffer, MAXLINE,  MSG_WAITALL, (struct sockaddr *) server_addr, len);
    (*pkts_counter)++;
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
  this->sent_pkts_counter_ = 0;
  this->real_test_time_ = 0;

  send_recv_msg_loop_args.sock_fd = this->tnet_socket_.get_socket(&this->tnet_socket_);
  send_recv_msg_loop_args.server_sock_addr = socket_client_address;
  send_recv_msg_loop_args.buffer = msg_to_send_buffer;
  send_recv_msg_loop_args.buffer_size = msg_send_size;
  send_recv_msg_loop_args.recv_addr_len = &len;
  send_recv_msg_loop_args.interrrupt_thread = &this->stop_thread_;
  send_recv_msg_loop_args.amount_of_packets_sent_by_client = &this->sent_pkts_counter_;
  send_recv_msg_loop_args.msg_size = this->tnet_settings_->msg_bytes_length_;
  send_recv_msg_loop_args.real_test_time = &this->real_test_time_;

  if(pthread_create(&this->thread_id_, NULL, client_send_and_recv_msg_loop_thread, &send_recv_msg_loop_args) != 0){

    LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Failed to launch client_send_and_recv_msg_loop_thread");
    return false;
  }
  LOG_DEBUG("%s%ld%s", "[TouchstoNetSocketConnection] Thread id of client_send_and_recv_msg_loop_thread: [",this->thread_id_, "]");
  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Launched client_send_and_recv_msg_loop_thread successfully");

  pthread_create(&this->statistic_thread_id_, NULL, client_statistic_thread, &send_recv_msg_loop_args);

  pthread_join(this->thread_id_, NULL);
  pthread_join(this->statistic_thread_id_, NULL);

  return true;
}

bool stop_working_thread(struct TouchstoNetSocketConnection *this) {

  this->stop_thread_ = true;
  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Working thread has been stopped");
  pthread_cancel(this->thread_id_);

  pthread_cancel(this->statistic_thread_id_);
  LOG_DEBUG("%s", "[TouchstoNetSocketConnection] Statistic thread has been stopped");

  LOG_DEBUG("%s%ld%s", "[TouchstoNetSocketConnection] Thread: [",this->thread_id_, "] has been cancelled");
  printf("%s", "\n"); /* new line after [Instant figures] */

  print_summary(this);
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
    .sent_pkts_counter_ = 0,
    .real_test_time_ = 0,
  };
}

const struct TouchstoNetSocketConnectionClass TouchstoNetSocketConnection = { .new = &newSocketConnection };
