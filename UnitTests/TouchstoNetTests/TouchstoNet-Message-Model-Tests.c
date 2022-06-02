/*
 * TouchstoNet-Message-Model-Tests.c
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

#define TEST_MESSAGE_SIZE      128
#define TEST_INVALID_SIZE_MAX  MESSAGE_MODEL_BUFFER_SIZE + 1
#define TEST_BUFFER_CONTENT    "TEST CONTENT"
#define TEST_INVALID_SIZE      -1

void MessageModelTest_prepare_message_with_size_128_bytes_and_true_returned() {

  struct TouchstoNetMessageModel message_model = TouchstoNetMessageModel.new();
  TEST_ASSERT_TRUE(message_model.prepare_message(&message_model, TEST_MESSAGE_SIZE));
}

void MessageModelTest_prepare_message_with_size_128_bytes_and_message_size_filed_is_set_to_128() {

  struct TouchstoNetMessageModel message_model = TouchstoNetMessageModel.new();
  message_model.prepare_message(&message_model, TEST_MESSAGE_SIZE);

  TEST_ASSERT_EQUAL(TEST_MESSAGE_SIZE, message_model.message_size_);
}

void MessageModelTest_prepare_message_with_size_128_bytes_and_buffer_has_128_bytes_allocated() {

  struct TouchstoNetMessageModel message_model = TouchstoNetMessageModel.new();
  message_model.prepare_message(&message_model, TEST_MESSAGE_SIZE);

  size_t allocated_data_length = strnlen(message_model.message_model_buffer_, MESSAGE_MODEL_BUFFER_SIZE);
  TEST_ASSERT_EQUAL(TEST_MESSAGE_SIZE, allocated_data_length);
}

void MessageModelTest_prepare_message_with_invalid_max_size_and_false_returned() {

  struct TouchstoNetMessageModel message_model = TouchstoNetMessageModel.new();
  TEST_ASSERT_FALSE(message_model.prepare_message(&message_model, TEST_INVALID_SIZE_MAX));
}

void MessageModelTest_prepare_message_with_invalid_size_and_false_returned() {

  struct TouchstoNetMessageModel message_model = TouchstoNetMessageModel.new();
  TEST_ASSERT_FALSE(message_model.prepare_message(&message_model, TEST_INVALID_SIZE));
}


void MessageModelTest_prepare_message_with_test_content_and_buffer_content_is_the_same() {

  struct TouchstoNetMessageModel message_model = TouchstoNetMessageModel.new();
  strncpy(message_model.message_model_buffer_, TEST_BUFFER_CONTENT, MESSAGE_MODEL_BUFFER_SIZE);

  TEST_ASSERT_TRUE(strncmp( message_model.get_buffer(&message_model), TEST_BUFFER_CONTENT, MESSAGE_MODEL_BUFFER_SIZE) == 0);
}

void MessageModelTest_prepare_message_with_size_128_bytes_and_get_msg_size_returns_size_128_bytes() {

  struct TouchstoNetMessageModel message_model = TouchstoNetMessageModel.new();
  message_model.prepare_message(&message_model, TEST_MESSAGE_SIZE);
  TEST_ASSERT_EQUAL(message_model.get_msg_size(&message_model), TEST_MESSAGE_SIZE);
}

