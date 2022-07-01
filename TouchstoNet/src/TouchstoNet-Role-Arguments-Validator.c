/*
 * TouchstoNet-Role-Arguments-Validator.c
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

#ifndef SRC_TOUCHSTONET_ROLE_ARGUMENTS_VALIDATOR_C_
#define SRC_TOUCHSTONET_ROLE_ARGUMENTS_VALIDATOR_C_

#include "TouchstoNet-Role-Arguments-Validator.h"
#include "LoggerC.h"

bool validate_arguments_for_role(struct TouchstoNetSettings *tnet_settings) {

  if (!tnet_settings->tnet_setting_flags_.get_ip_address_status(&tnet_settings->tnet_setting_flags_) && tnet_settings->get_role(tnet_settings) == CLIENT) {

    LOG_DEBUG("%s", "[TouchstoNetRoleArgumentsValidator] No IP address argument. Default IP address used");
    LOG_WARNING("%s", "No IP address argument. Default IP address used");
  } else if (tnet_settings->tnet_setting_flags_.get_ip_address_status(&tnet_settings->tnet_setting_flags_)
      && tnet_settings->get_role(tnet_settings) == SERVER) {

    LOG_DEBUG("%s", "[TouchstoNetRoleArgumentsValidator] No IP address needed for server. IP address argument ignored");
    LOG_ERROR("%s", "No IP address argument needed for server");
    return false;
  }

  if (!tnet_settings->tnet_setting_flags_.get_msg_bytes_length_status(&tnet_settings->tnet_setting_flags_)
      && tnet_settings->get_role(tnet_settings) == CLIENT) {

    LOG_DEBUG("%s", "[TouchstoNetRoleArgumentsValidator] No message length argument. Default message length used");
    LOG_WARNING("%s", "No message length argument. Default message length used");
  } else if (tnet_settings->tnet_setting_flags_.get_msg_bytes_length_status(&tnet_settings->tnet_setting_flags_)
      && tnet_settings->get_role(tnet_settings) == SERVER) {

    LOG_DEBUG("%s", "[TouchstoNetRoleArgumentsValidator] No message length argument needed. Message length argument ignored");
    LOG_ERROR("%s", "No message length argument needed for server");
    return false;
  }

  if (!tnet_settings->tnet_setting_flags_.get_test_duration_status(&tnet_settings->tnet_setting_flags_) && tnet_settings->get_role(tnet_settings) == CLIENT) {

    LOG_DEBUG("%s", "[TouchstoNetRoleArgumentsValidator] No test time argument. Default test time used");
    LOG_WARNING("%s", "No test time argument. Default test time used");
  } else if (tnet_settings->tnet_setting_flags_.get_test_duration_status(&tnet_settings->tnet_setting_flags_)
      && tnet_settings->get_role(tnet_settings) == SERVER) {

    LOG_DEBUG("%s", "[TouchstoNetRoleArgumentsValidator] No test time argument needed for server. Test time argument ignored");
    LOG_ERROR("%s", "No test time argument needed for server. Test time argument ignored");
    return false;
  }

  if (!tnet_settings->tnet_setting_flags_.get_port_number_status(&tnet_settings->tnet_setting_flags_)
      && (tnet_settings->get_role(tnet_settings) == CLIENT || tnet_settings->get_role(tnet_settings) == SERVER)) {

    LOG_DEBUG("%s", "[TouchstoNetRoleArgumentsValidator] No port number argument. Default port number used");
    LOG_WARNING("%s", "No port number argument. Default port number used");
  }

  return true;
}


static struct TouchstoNetRoleArgumentsValidator newRoleArgumentsValidator() {
  return (struct TouchstoNetRoleArgumentsValidator) {
    .validate_arguments_for_role = &validate_arguments_for_role,
  };
}
const struct TouchstoNetRoleArgumentsValidatorClass TouchstoNetRoleArgumentsValidator = { .new = &newRoleArgumentsValidator };

#endif /* SRC_TOUCHSTONET_ROLE_ARGUMENTS_VALIDATOR_C_ */
