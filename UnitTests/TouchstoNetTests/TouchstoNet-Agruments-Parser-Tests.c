/*
 * TouchstoNet-Agruments-Parser-Tests.c
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

/*#include "../../TouchstoNet/src/TouchstoNet-Agruments-Parser.c"*/ /* file already included in TouchstoNet-Engine-Tests.c */

#define TEST_FAKE_PORT_NUMBER 7777

void AgrumentsParserTest_inject_settings_with_set_port_number_and_it_is_set_in_arguments_parser() {

  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_settings.port_number_ = TEST_FAKE_PORT_NUMBER;

  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_EQUAL(tnet_arguments_parser.tnet_settings_->port_number_, TEST_FAKE_PORT_NUMBER);
}

void AgrumentsParserTest_inject_settings_and_true_is_returned() {

  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();

  TEST_ASSERT_TRUE(tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings));
}

void AgrumentsParserTest_try_inject_settings_with_null_pointer_and_false_returned() {

  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings* tnet_null_settings = NULL;

  TEST_ASSERT_FALSE(tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, tnet_null_settings));
}

/*void AgrumentsParserTest_() {

}

void AgrumentsParserTest_() {

}

void AgrumentsParserTest_() {

}*/
