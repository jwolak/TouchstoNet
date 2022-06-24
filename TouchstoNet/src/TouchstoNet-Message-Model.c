/*
 * TouchstoNet-Message-Model.c
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

#include "TouchstoNet-Message-Model.h"

#include "LoggerC.h"

#include <string.h>

bool prepare_message (struct TouchstoNetMessageModel *this, int32_t msg_size) {

  if (msg_size > MESSAGE_MODEL_BUFFER_SIZE || msg_size < 0) {

    LOG_DEBUG("%s", "[TouchstoNetMessageModel] Message size invalid");
    LOG_ERROR("%s", "Message size invalid");
    return false;
  }

  if (!memset(this->message_model_buffer_, 0x1, msg_size)) {

    LOG_DEBUG("%s", "[TouchstoNetMessageModel] Failed to allocate message buffer");
    return false;
  }

  this->message_size_ = msg_size;

  LOG_DEBUG("%s%d", "[TouchstoNetMessageModel] Prepared message with size: ", msg_size);
  return true;
}

char *get_buffer (struct TouchstoNetMessageModel *this) {

  return this->message_model_buffer_;
}

int32_t get_msg_size (struct TouchstoNetMessageModel *this) {

  return this->message_size_;
}

static struct TouchstoNetMessageModel newMessageModel() {
  return (struct TouchstoNetMessageModel) {
    .prepare_message = &prepare_message,
    .get_buffer = &get_buffer,
    .get_msg_size = &get_msg_size,
  };
}

const struct TouchstoNetMessageModelClass TouchstoNetMessageModel = { .new = &newMessageModel };
