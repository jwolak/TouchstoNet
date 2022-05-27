/*
 * TouchstoNet-Socket.c
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

#include "TouchstoNet-Socket.h"

#include <sys/socket.h>

#include <unistd.h>

#include "LoggerC.h"

bool create_udp(struct TouchstoNetSocket *this) {

  LOG_DEBUG("%s", "TouchstoNetSocket creates UDP socket");

  if ((this->socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {

    LOG_ERROR("%s", "TouchstoNetSocket UDP socket create failed");
    return false;
  }

  LOG_DEBUG("%s", "TouchstoNetSocket UDP socket create successful");
  return true;
}

bool create_tcp(struct TouchstoNetSocket *this) {

  LOG_DEBUG("%s", "TouchstoNetSocket creates TCP socket");

  if ((this->socket_fd_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {

    LOG_ERROR("%s", "TouchstoNetSocket TCP socket create failed");
    return false;
  }

  LOG_DEBUG("%s", "TouchstoNetSocket TCP socket create successful");
  return true;
}

bool close_socket(struct TouchstoNetSocket *this) {

  LOG_DEBUG("%s", "TouchstoNetSocket closes socket");

  if (close(this->socket_fd_) != 0) {

    LOG_ERROR("%s", "TouchstoNetSocket socket to close failed");
    return false;
  }

  LOG_DEBUG("%s", "TouchstoNetSocket socket closed successful");
  return true;
}

int get_socket(struct TouchstoNetSocket *this) {

  return this->socket_fd_;
}

static struct TouchstoNetSocket newSocket() {
  return (struct TouchstoNetSocket) {
    .create_udp = &create_udp,
    .create_tcp = &create_tcp,
    .close_socket = &close_socket,
    .get_socket = &get_socket,
  };
}

const struct TouchstoNetSocketClass TouchstoNetSocket = { .new = &newSocket };

