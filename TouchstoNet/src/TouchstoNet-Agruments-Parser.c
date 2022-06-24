/*
 * TouchstoNet-Agruments-Parser.c
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

#include "TouchstoNet-Agruments-Parser.h"
#include "LoggerC.h"

#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TNET_IP_ADDRESS_BUFFER_SIZE   INET_ADDRSTRLEN
#define TNET_MIN_NUMBER_OF_ARGUMENTS  2

static void print_help() {

  char help_buffer [] =
      "\n\t#Menu:\n"
      "\t [--help]    or [-h] print help\n"
      "\t [--server]  or [-s] enable server mode\n"
      "\t [--client]  or [-c] enable client mode\n"
      "\t [--port]    or [-p] port number\n"
      "\t [--address] or [-a] server IP address\n"
      "\t [--time]    or [-t] test duration in seconds\n"
      "\t [--bytes]   or [-l] message size in bytes\n"
      "\n"
      "\t#Limitations:\n"
      "\t Port range        for [--port]  is: 1 - 65535\n"
      "\t Max test time     for [--time]  is: 3600 [s]\n"
      "\t Message max size  for [--bytes] is: 1024 [bytes]\n"
      "\n"
      "\t#Examples of client and server set:\n"
      "\t Client: TouchstoNet -c -p 1024 -a 192.168.0.1 -t 10 -l 64\n"
      "\t Server: TouchstoNet -s -p 1024\n"
      "\n"
      "\t Client: TouchstoNet --client --port 1024 -address 192.168.0.1 -time 10 -bytes 64\n"
      "\t Server: TouchstoNet --server --port 1024\n"
      "\n"
      "\t#Remarks:\n"
      "\t No [--server] or [--client] argument sets default role to client\n"
      "\t No [--time] argument for client sets default max time: 3600[s]\n"
      "\t No [--port] argument for server and client sets default value to port 1024\n"
      "\t No [--bytes] argument for client sets default message size to 128 bytes\n"
      "\t No [--address] argument for client sets default IP address to 0.0.0.0\n"
      "\n\t [IMPORTANT!] Server mode has only port number argument allowed\n";

  char copyrights_buffer [] =
                           "\t Copyrights: Janusz Wolak\n"
                           "\t e-mail:     januszvdm@gmail.com\n"
                           "\t web:        github.com/jwolak\n\n";
  char logo_buffer [] =
      "      _______               _         _                   _   _      _\n"
      "     |__   __|             | |       | |                 | \\ | |    | |\n"
      "        | | ___  _   _  ___| |__  ___| |_ ___  _ __   ___|  \\| | ___| |_\n"
      "        | |/ _ \\| | | |/ __| '_ \\/ __| __/ _ \\| '_ \\ / _ \\ . ` |/ _ \\ __|\n"
      "        | | (_) | |_| | (__| | | \\__ \\ || (_) | | | |  __/ |\\  |  __/ |_\n"
      "        |_|\\___/ \\__,_|\\___|_| |_|___/\\__\\___/|_| |_|\\___|_| \\_|\\___|\\__|\n";

  printf("%s", logo_buffer);
  printf("%s\n", help_buffer);
  printf("\n%s", copyrights_buffer);
}

bool inject_settings_to_args_parser(struct TouchstoNetAgrumentsParser* this, struct TouchstoNetSettings* tnet_settings_to_injected){

  if(!tnet_settings_to_injected) {

    LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] settings pointer is null");
    LOG_ERROR("%s", "settings pointer is null");
    return false;
  }

  this->tnet_settings_ = tnet_settings_to_injected;

  LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] Settings injected successfully to ArgumentsParser");
  return true;
}

bool parse_arguments(struct TouchstoNetAgrumentsParser* this, int32_t argc, char **argv) {

  int flag = 0;
  int32_t portno;
  char address_parameter[TNET_IP_ADDRESS_BUFFER_SIZE];
  uint32_t test_time;
  int32_t msg_bytes_length;

  static struct option longopts[] = {
      {"help",    no_argument,        NULL,  'h'},
      {"server",  no_argument,        NULL,  's'},
      {"client",  no_argument,        NULL,  'c'},
      {"port",    required_argument,  NULL,  'p'},
      {"address", required_argument,  NULL,  'a'},
      {"time",    required_argument,  NULL,  't'},
      {"bytes",   required_argument,  NULL,  'l'},
  };

  if (argc < TNET_MIN_NUMBER_OF_ARGUMENTS) {

    LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] No arguments")
    LOG_ERROR("%s", "No arguments provided");
    print_help();
    return false;
  }

  printf("\n");
  for (int i = 0; i < argc; ++i) {
    LOG_DEBUG("[TouchstoNetAgrumentsParser] argv[%d]: %s", i, argv[i]);
  }
  printf("\n");

  while ((flag = getopt_long(argc, argv, "hscp:a:t:l:", longopts, NULL)) != -1) {
    switch (flag) {
    case 's':
      if (!this->tnet_settings_->set_role(this->tnet_settings_, SERVER)) {

        LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] Server role parse failed");
        LOG_ERROR("%s", "Server role parse failed");
        return false;
      }

      LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] Server mode is set");
      break;

    case 'c':
      if (!this->tnet_settings_->set_role(this->tnet_settings_, CLIENT)) {

        LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] Client role parse failed");
        LOG_ERROR("%s", "Client role parse failed");
        return false;
      }

      LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] Client mode is set");
      break;

    case 'p':
      portno = atoi(optarg);

      if (!this->tnet_settings_->set_port_number(this->tnet_settings_, portno)) {

        LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] Port number parse failed");
        LOG_ERROR("%s", "Port number parse failed");
        return false;
      }

      LOG_DEBUG("%s%d", "[TouchstoNetAgrumentsParser] Port number set: ", portno);
      break;

    case 'a':
      strncpy(address_parameter, optarg, TNET_IP_ADDRESS_BUFFER_SIZE);

      if (!this->tnet_settings_->set_ip_address(this->tnet_settings_, address_parameter)) {

        LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] IPv4 address parse failed");
        LOG_ERROR("%s", "IPv4 address parse failed");
        return false;
      }

      LOG_DEBUG("%s%s", "[TouchstoNetAgrumentsParser] IP address that has been set: ", address_parameter);
      break;

    case 't':
      test_time = atoi(optarg);

      if (!this->tnet_settings_->set_test_duration(this->tnet_settings_, test_time)) {

        LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] Test duration time parse failed");
        LOG_ERROR("%s", "Test duration time parse failed");
        return false;
      }

      LOG_DEBUG("%s%d", "[TouchstoNetAgrumentsParser] Test duration set to: ", test_time);
      break;

    case 'l':
      msg_bytes_length = atoi(optarg);

      if (!this->tnet_settings_->set_msg_bytes_length(this->tnet_settings_, msg_bytes_length)) {

        LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] Message length in bytes parse failed");
        LOG_ERROR("%s", "Message length in bytes parse failed");
        return false;
      }

      LOG_DEBUG("%s%d", "[TouchstoNetAgrumentsParser] Message length in bytes set to: ", msg_bytes_length);
      break;

    case 'h':
    default:
      LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] Help printed");
      print_help();
      break;
    }
  }

  LOG_DEBUG("%s", "[TouchstoNetAgrumentsParser] Parse settings successful");
  return true;
}

static struct TouchstoNetAgrumentsParser newArgumentsParser() {
  return (struct TouchstoNetAgrumentsParser) {
    .parse_arguments = &parse_arguments,
    .inject_settings_to_args_parser = &inject_settings_to_args_parser
  };
}
const struct TouchstoNetAgrumentsParserClass TouchstoNetAgrumentsParser = { .new = &newArgumentsParser };

