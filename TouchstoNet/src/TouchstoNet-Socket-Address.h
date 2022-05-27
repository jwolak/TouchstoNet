/*
 * TouchstoNet-Socket-Address.h
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

#ifndef SRC_TOUCHSTONET_SOCKET_ADDRESS_H_
#define SRC_TOUCHSTONET_SOCKET_ADDRESS_H_

#include <stdbool.h>
#include <stdint.h>

#include <netinet/in.h>

struct TouchstoNetSocketAddress {

  /*public*/
  bool(*set_address_family)(struct TouchstoNetSocketAddress *this, int16_t address_family_to_set);
  bool(*set_ip_port)(struct TouchstoNetSocketAddress *this, uint16_t port_number_to_set);
  bool(*set_inet_address)(struct TouchstoNetSocketAddress *this, in_addr_t inet_address_to_set);

 int16_t(*get_address_family)(struct TouchstoNetSocketAddress *this);
 uint16_t(*get_ip_port)(struct TouchstoNetSocketAddress *this);
 in_addr_t(*get_inet_address)(struct TouchstoNetSocketAddress *this);

 struct sockaddr_in*(*get_socket_address)(struct TouchstoNetSocketAddress *this);


  /*private*/
  struct sockaddr_in socket_address_;

};

extern const struct TouchstoNetSocketAddressClass {
  struct TouchstoNetSocketAddress(*new)();
} TouchstoNetSocketAddress;

#endif /* SRC_TOUCHSTONET_SOCKET_ADDRESS_H_ */
