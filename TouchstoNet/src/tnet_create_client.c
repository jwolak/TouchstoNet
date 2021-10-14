/*
 * tnet_create_client.c
 *
 *  Created on: 2021
 *      Author: Janusz Wolak
 */

/*-
 * Copyright (c) 2021 Janusz Wolak  
 * All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT    8080

#include "tnet_debug.h"
#include "tnet_create_client.h"

bool tnet_create_client(struct tnet_new_test *new_test) {

	char *hello_message_client = "Hello from client";

	if (!tnet_create_socket_fd(new_test, AF_INET, SOCK_DGRAM, 0)) {
		tnet_debug("%s", "Create socket failed");
		return false;
	}

	if (!tnet_create_server_socket_address(&new_test, AF_INET, INADDR_ANY,
			PORT)) {
		tnet_debug("%s", "Create server address struct failed");
		return false;
	}

	tnet_send_data(new_test, hello_message_client, strlen(hello_message_client));
	tnet_receive_data(new_test);

	return true;
}
