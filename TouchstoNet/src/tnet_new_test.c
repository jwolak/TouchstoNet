/*
 * tnet_new_test.c
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
#include <string.h>
#include <sys/socket.h>

#include "tnet_debug.h"

#define MAXLINE 1024

static bool tnet_close_socket_fd(struct tnet_new_test* new_test);
static bool tnet_allocate_socket_address_struct(struct sockaddr_in** socket_address);
static void tnet_set_server_address_values(struct sockaddr_in* socket_address, int16_t addr_family, uint32_t addr_type, uint16_t addr_port);
static bool tnet_free_address_struct(struct sockaddr_in* socket_address);
static void tnet_reset_address_struct(struct sockaddr_in* socket_address);

bool tnet_create_new_test(struct tnet_new_test** new_test) {

	*new_test = (struct tnet_new_test*)malloc(sizeof(struct tnet_new_test));

	if (*new_test == NULL) {
		tnet_debug("%s", "Struct tnet_new_test allocation failed!");
		return false;
	}

	memset(*new_test, 0, sizeof(struct tnet_new_test));

	tnet_debug("%s", "Allocation of tnet_new_test successful");
	return true;
}


bool tnet_free_new_test(struct tnet_new_test* new_test) {

	if (new_test == NULL) {
		tnet_debug("%s", "Struct tnet_new_test is NULL!");
		return false;
	}

	if (new_test->socket_fd != 0) {
		if (!tnet_close_socket_fd(new_test)) {
			return false;
		}
	}

	if (new_test->server_socket_address_stuct != NULL) {
		if (!tnet_free_address_struct(new_test->server_socket_address_stuct)) {
			return false;
		}
	}

	free(new_test);

	tnet_debug("%s", "Free tnet_new_test successful");
	return true;
}

bool tnet_create_socket_fd(struct tnet_new_test* new_test, int32_t sock_domain, int32_t sock_type, int32_t sock_protocol) {

	if (!new_test) {
		tnet_debug("%s", "Struct tnet_new_test is NULL!");
		return false;
	}

    if ((new_test->socket_fd = socket(sock_domain, sock_type, sock_protocol)) < 0) {
    	tnet_debug("%s", "Socket creation failed");
        return false;
    }

    tnet_debug("%s", "Socket creation successful");
	return true;
}


bool tnet_create_server_socket_address(struct tnet_new_test** new_test, int16_t addr_family, uint32_t addr_type, uint16_t addr_port) {

	if (*new_test == NULL) {
		tnet_debug("%s", "Struct tnet_new_test is NULL!");
		return false;
	}

	if (!tnet_allocate_socket_address_struct(&(*new_test)->server_socket_address_stuct)) {
		tnet_debug("%s", "Allocation of server sockaddr_in failed");
		return false;
	}

	tnet_set_server_address_values((*new_test)->server_socket_address_stuct, addr_family, addr_type, addr_port);

	tnet_debug("%s", "Allocation of server sockaddr_in successful");
	return true;
}

bool tnet_create_client_socket_address(struct tnet_new_test** new_test) {

	if (*new_test == NULL) {
		tnet_debug("%s", "Struct tnet_new_test is NULL!");
		return false;
	}

	if (!tnet_allocate_socket_address_struct(&(*new_test)->client_socket_address_stuct)) {
		tnet_debug("%s", "Allocation of client sockaddr_in failed");
		return false;
	}

	tnet_debug("%s", "Allocation of client sockaddr_in successful");
	return true;
}

bool tnet_bind_to_socket(struct tnet_new_test* new_test) {

	if (new_test == NULL) {
		tnet_debug("%s", "Struct tnet_new_test is NULL!");
		return false;
	}

    if ( bind(new_test->socket_fd, (const struct sockaddr *)new_test->server_socket_address_stuct,
            sizeof(struct sockaddr_in)) < 0 )
    {
    	tnet_debug("%s", "Bind to socket failed");
        return false;
    }

	return true;
}


void tnet_receive_data(struct tnet_new_test* new_test) {

	char buffer[MAXLINE];
	socklen_t len;
	int n;

	len = sizeof(struct sockaddr);

	n = recvfrom(new_test->socket_fd, (char*) buffer, MAXLINE,
	MSG_WAITALL, (struct sockaddr*) new_test->client_socket_address_stuct,
			&len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);

}

void tnet_send_data(struct tnet_new_test* new_test) {

	char *hello = "Hello from server";

	sendto(new_test->socket_fd, (const char*) hello, strlen(hello),
	MSG_CONFIRM, (const struct sockaddr*) new_test->client_socket_address_stuct,
			sizeof(struct sockaddr));
	printf("Hello message sent.\n");
}

/*### static methods ###*/

static bool tnet_close_socket_fd(struct tnet_new_test *new_test) {

	if (shutdown(new_test->socket_fd, SHUT_RDWR) != 0) {
		tnet_debug("%s", "Close socket failed!");
		return false;
	}

	tnet_debug("%s", "Close socket successful");
	return true;
}

static void tnet_reset_address_struct(struct sockaddr_in* socket_address) {
	memset(socket_address, 0, sizeof(struct sockaddr_in));
}


static bool tnet_allocate_socket_address_struct(struct sockaddr_in** socket_address) {

	*socket_address = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));

	if (*socket_address == NULL) {
		tnet_debug("%s", "Struct sockaddr_in allocation failed!");
		return false;
	}

	tnet_reset_address_struct(*socket_address);

	tnet_debug("%s", "Allocation of sockaddr_in successful");
	return true;
}

static void tnet_set_server_address_values(struct sockaddr_in* socket_address, int16_t addr_family, uint32_t addr_type, uint16_t addr_port) {

	socket_address->sin_family = addr_family;
	socket_address->sin_addr.s_addr = addr_type;
	socket_address->sin_port = htons(addr_port);
}

static bool tnet_free_address_struct(struct sockaddr_in* socket_address) {

	if (!socket_address) {
		tnet_debug("%s", "Struct sockaddr_in is NULL!");
		return false;
	}

	free(socket_address);

	tnet_debug("%s", "Struct sockaddr_in release successful");
	return true;
}
