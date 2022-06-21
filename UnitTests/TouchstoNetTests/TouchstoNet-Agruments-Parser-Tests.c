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


/*
 * [IMPORTANT]
 *
 * Why before each test set optind = 0;
 * extern int optind to zero;
 * The variable optind is the index of the next element to be processed in argv.
 * The system initializes this value to 1. The caller can reset it to 1 to restart scanning of the same argv, or when scanning a new argument vector.
 */

#define TEST_FAKE_PORT_NUMBER 7777

char kTestProgramName[] = "TestAppName";
char* kEmptyCommandLineArgument[] = {kTestProgramName};
char* kPrintHelpCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-h"};
char* kServerCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-s"};
char* kClientCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-c"};
char* kValidPortCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-p 1026"};
char* kInvalidZeroPortCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-p 0"};
char* kInvalidMaxPortCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-p 65536"};
char* kValidIpAddressCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-a 192.168.1.1"};
char* kInvalidIpAddressCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-a 289.300.1.1"};
char* kInvalidSignsInIpAddressCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-a @@.300.#.1"};
char* kValidTestTimeCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-t 26"};
char* kValidMinumumTestTimeCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-t 1"};
char* kValidMaximumTestTimeCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-t 3600"};
char* kInvalidMinumumTestTimeCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-t 0"};
char* kInvalidMaximumTestTimeCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-t 3601"};
char* kInvalidNegativeTestTimeCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-t -36"};
char* kValidMessageSizeCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-l 256"};
char* kInvalidMessageSizeZeroCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-l 0"};
char* kInvalidNegativeMessageSizeCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-l -16"};
char* kValidMaxMessageSizeCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-l 1024"};
char* kInvalidMaxMessageSizeCommandLineArgument[] = {(char*)kTestProgramName, (char*)"-l 1025"};

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

void AgrumentsParserTest_try_to_no_arguments_provide_and_false_returned() {

/*
 * Why before each test set optind = 0;
 * extern int optind to zero;
 * The variable optind is the index of the next element to be processed in argv.
 * The system initializes this value to 1. The caller can reset it to 1 to restart scanning of the same argv, or when scanning a new argument vector.
 */
  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 1, kEmptyCommandLineArgument));
}

void AgrumentsParserTest_provide_help_print_argument_and_true_returned() {

  optind = 0; /*The variable optind is the index of the next element to be processed in argv.*/
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();

  TEST_ASSERT_TRUE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kPrintHelpCommandLineArgument));
}

void AgrumentsParserTest_provide_server_mode_argument_and_server_role_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kServerCommandLineArgument);
  TEST_ASSERT_EQUAL(tnet_arguments_parser.tnet_settings_->role_, SERVER);
}

void AgrumentsParserTest_no_role_provided_and_default_role_set_to_client_mode() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_EQUAL(tnet_arguments_parser.tnet_settings_->role_, CLIENT);
}

void AgrumentsParserTest_provide_client_mode_argument_and_client_role_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kClientCommandLineArgument);
  TEST_ASSERT_EQUAL(tnet_arguments_parser.tnet_settings_->role_, CLIENT);
}

void AgrumentsParserTest_provide_valid_port_number_and_port_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kValidPortCommandLineArgument);
  TEST_ASSERT_EQUAL(tnet_arguments_parser.tnet_settings_->port_number_, 1026);
}

void AgrumentsParserTest_try_set_invalid_zero_port_number_and_false_returned() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kInvalidZeroPortCommandLineArgument));
}

void AgrumentsParserTest_try_set_invalid_max_port_number_and_false_returned() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kInvalidMaxPortCommandLineArgument));
}

void AgrumentsParserTest_provide_valid_IP_address_and_IP_address_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kValidIpAddressCommandLineArgument);
  TEST_ASSERT_EQUAL(inet_addr("192.168.1.1"), tnet_settings.ip_address_);
}

void AgrumentsParserTest_provide_invalid_IP_address_and_false_is_returned() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kInvalidIpAddressCommandLineArgument));
}

void AgrumentsParserTest_provide_invalid_signs_in_IP_address_and_false_is_returned() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kInvalidSignsInIpAddressCommandLineArgument));
}

void AgrumentsParserTest_provide_valid_test_time_and_it_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kValidTestTimeCommandLineArgument);

  TEST_ASSERT_EQUAL(26, tnet_arguments_parser.tnet_settings_->test_duration_);
}

void AgrumentsParserTest_provide_valid_test_time_and_true_is_returned() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_TRUE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kValidTestTimeCommandLineArgument));
}

void AgrumentsParserTest_provide_valid_minimum_test_time_and_it_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kValidMinumumTestTimeCommandLineArgument);
  TEST_ASSERT_EQUAL(1, tnet_arguments_parser.tnet_settings_->test_duration_);
}

void AgrumentsParserTest_provide_invalid_minimum_test_time_and_it_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kInvalidMinumumTestTimeCommandLineArgument));
}

void AgrumentsParserTest_provide_valid_maximum_test_time_and_it_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kValidMaximumTestTimeCommandLineArgument);
  TEST_ASSERT_EQUAL(3600, tnet_arguments_parser.tnet_settings_->test_duration_);
}

void AgrumentsParserTest_provide_invalid_maximum_test_time_and_false_is_returned() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kInvalidMaximumTestTimeCommandLineArgument));
}

void AgrumentsParserTest_provide_invalid_negative_test_time_and_false_is_returned() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kInvalidNegativeTestTimeCommandLineArgument));
}

void AgrumentsParserTest_not_provided_test_time_for_client_and_zero_time_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kClientCommandLineArgument);

  TEST_ASSERT_EQUAL(0, tnet_arguments_parser.tnet_settings_->test_duration_);
}

void AgrumentsParserTest_valid_message_size_provided_and_it_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kValidMessageSizeCommandLineArgument);

  TEST_ASSERT_EQUAL(256, tnet_arguments_parser.tnet_settings_->msg_bytes_length_);
}

void AgrumentsParserTest_invalid_zero_message_size_provided_and_flase_returned() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kInvalidMessageSizeZeroCommandLineArgument));
}

void AgrumentsParserTest_invalid_negative_message_size_provided_and_flase_returned() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kInvalidNegativeMessageSizeCommandLineArgument));
}

void AgrumentsParserTest_valid_maximum_message_size_provided_and_it_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kValidMaxMessageSizeCommandLineArgument);

  TEST_ASSERT_EQUAL(1024, tnet_arguments_parser.tnet_settings_->msg_bytes_length_);
}

void AgrumentsParserTest_invalid_maximum_message_size_provided_and_it_is_set() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  TEST_ASSERT_FALSE(tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kInvalidMaxMessageSizeCommandLineArgument));
}

void AgrumentsParserTest_no_message_size_provided_and_it_is_set_to_default() {

  optind = 0;
  struct TouchstoNetAgrumentsParser tnet_arguments_parser = TouchstoNetAgrumentsParser.new();
  struct TouchstoNetSettings tnet_settings = TouchstoNetSettings.new();
  tnet_arguments_parser.inject_settings_to_args_parser(&tnet_arguments_parser, &tnet_settings);

  tnet_arguments_parser.parse_arguments(&tnet_arguments_parser, 2, kClientCommandLineArgument);

  TEST_ASSERT_EQUAL(128, tnet_arguments_parser.tnet_settings_->msg_bytes_length_);
}
