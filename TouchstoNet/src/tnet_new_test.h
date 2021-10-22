/*
 * tnet_new_test.h
 *
 *  Created on: 2021
 *      Author: Janusz Wolak
 */

/*-
 * Copyright (c) 2021 Janusz Wolak  
 * All rights reserved.
 *
 */
#ifndef SRC_TNET_NEW_TEST_H_
#define SRC_TNET_NEW_TEST_H_

#include <stdbool.h>
#include <stdint.h>
#include <netinet/in.h>

#include "tnet_new_test.h"

enum tnet_role {
	CLIENT = 1,
	SERVER = 2
};

struct tnet_new_test {
	enum tnet_role		role;
	int32_t 			socket_fd;
	struct sockaddr_in  *server_socket_address_stuct;
	struct sockaddr_in  *client_socket_address_stuct;
	int32_t 			port_no;
	in_addr_t 			ip_address;
	char				*pidfile;
};

bool tnet_create_new_test(struct tnet_new_test** new_test);

bool tnet_free_new_test(struct tnet_new_test* new_test);

bool tnet_create_socket_fd(struct tnet_new_test* new_test, int32_t sock_domain, int32_t sock_type, int32_t sock_protocol);

bool tnet_create_server_socket_address(struct tnet_new_test** new_test, int16_t addr_family, uint32_t addr_type, uint16_t addr_port);

bool tnet_create_client_socket_address(struct tnet_new_test** new_test);

bool tnet_bind_to_socket(struct tnet_new_test* new_test);

void tnet_receive_data(struct tnet_new_test* new_test);

void tnet_send_data(struct tnet_new_test* new_test, char* message, int32_t msg_length);

bool tnet_create_pid_file(struct tnet_new_test* new_test);

bool tnet_delete_pid_file(struct tnet_new_test* new_test);

#endif /* SRC_TNET_NEW_TEST_H_ */
