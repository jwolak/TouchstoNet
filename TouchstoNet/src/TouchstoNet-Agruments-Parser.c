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

#define TNET_IP_ADDRESS_BUFFER_SIZE   16

bool inject_settings_to_args_parser(struct TouchstoNetAgrumentsParser* this, struct TouchstoNetSettings* tnet_settings_to_injected){

  if(!tnet_settings_to_injected) {

    LOG_ERROR("%s", "settings pointer is null");
    return false;
  }

  this->tnet_settings_ = tnet_settings_to_injected;

  LOG_DEBUG("%s", "Settings injected successfully to ArgumentsParser");
  return true;
}

bool parse_arguments(struct TouchstoNetAgrumentsParser* this, int32_t argc, char **argv) {

  int flag;
  int32_t portno;
  char address_parameter[TNET_IP_ADDRESS_BUFFER_SIZE];
  uint32_t test_time;

  static struct option longopts[] = {
      {"help",    no_argument, NULL, 'h' },
      {"server",  no_argument, NULL, 's' },
      {"client",  no_argument, NULL, 'c' },
      {"port",    required_argument, NULL, 'p'},
      {"address", required_argument, NULL, 'a'},
      {"time",    required_argument, NULL, 't'},
  };

  while ((flag = getopt_long(argc, argv, "hscp:a:t:", longopts, NULL)) != -1) {
    switch (flag) {
    case 's':
      if (!this->tnet_settings_->set_role(this->tnet_settings_, SERVER)) {

        LOG_ERROR("%s", "Role parse failed");
        return false;
      }

      LOG_DEBUG("%s", "Server mode is set");
      break;

    case 'c':
      if (this->tnet_settings_->set_role(this->tnet_settings_, CLIENT)) {

        LOG_ERROR("%s", "Role parse failed");
        return false;
      }

      LOG_DEBUG("%s", "Client mode is set");
      break;

    case 'p':
      portno = atoi(optarg);

      if (!this->tnet_settings_->set_port_number(this->tnet_settings_, portno)) {

        LOG_ERROR("%s", "Port number parse failed");
        return false;
      }

      LOG_DEBUG("%s%d", "Port number set:", portno);
      break;

    case 'a':
      strncpy(address_parameter, optarg, TNET_IP_ADDRESS_BUFFER_SIZE);

      if (!this->tnet_settings_->set_ip_address(this->tnet_settings_, address_parameter)) {

        LOG_ERROR("%s", "IP address parse failed");
        return false;
      }

      LOG_DEBUG("%s%s", "IP address set:", address_parameter);
      break;

    case 't':
      test_time = atoi(optarg);

      if (!this->tnet_settings_->set_test_duration(this->tnet_settings_, test_time)) {

        LOG_ERROR("%s", "Test duration time parse failed");
        return false;
      }

      LOG_DEBUG("%s%d", "Test duration set to: ", test_time);
      break;

    case 'h':
    default:
     /* printf("%s","\nHelp:\n");*/
      break;
    }
  }

  LOG_DEBUG("%s", "Parse settings successful");
  return true;
}

static struct TouchstoNetAgrumentsParser newArgumentsParser() {
  return (struct TouchstoNetAgrumentsParser) {
    .parse_arguments = &parse_arguments,
    .inject_settings_to_args_parser = &inject_settings_to_args_parser
  };
}
const struct TouchstoNetAgrumentsParserClass TouchstoNetAgrumentsParser = { .new = &newArgumentsParser };

