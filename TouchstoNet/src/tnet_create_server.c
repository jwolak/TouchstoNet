/*
 * tnet_create_server.c
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080


#include "tnet_create_server.h"
#include "tnet_debug.h"

bool tnet_create_server(struct tnet_new_test* new_test) {

		int sockfd;
	    char *hello = "Hello from server";
	    struct sockaddr_in servaddr, cliaddr;

	    if (!tnet_create_socket_fd(new_test, AF_INET, SOCK_DGRAM, 0)) {
	    	tnet_debug("%s", "Create socket failed");
	    	return false;
	    }

	    if (!tnet_create_server_socket_address(&new_test, AF_INET, INADDR_ANY, PORT)) {
	    	tnet_debug("%s", "Create server address struct failed");
	    	return false;
	    }

	    if (!tnet_create_client_socket_address(&new_test)) {
	    	tnet_debug("%s", "Create client address struct failed");
	    	return false;
	    }

	    if (!tnet_bind_to_socket(new_test)) {
	    	return false;
	    }

	    tnet_receive_data(new_test);

	    tnet_send_data(new_test, "Hello from server", strlen("Hello from server"));


	return true;
}
