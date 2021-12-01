/*
 * tnet_arguments_parser.c
 *
 *  Created on: 2021
 *      Author: Janusz Wolak
 */

/*-
 * Copyright (c) 2021 Janusz Wolak  
 * All rights reserved.
 *
 */

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>

#include "tnet_error.h"
#include "tnet_debug.h"
#include "tnet_arguments_parser.h"

#define TNET_MAX_PORT_NUMBER		65535
#define TNET_MIN_PORT_NUMBER		1
#define TNET_IP_ADDRESS_BUFFER_SIZE	16

static bool tnet_validate_port_number(int32_t port_number);
static bool tnet_validate_ip_address(struct tnet_new_test* new_test, char* ip_addr);
static bool tnet_validate_test_duration_time(uint32_t test_duration_time);
static bool tnet_validate_aguments_by_mode(struct tnet_new_test* new_test);

bool tnet_parse_arguments(struct tnet_new_test* new_test, int32_t argc, char **argv) {

	int flag;
	int32_t portno;
	char address_parameter[TNET_IP_ADDRESS_BUFFER_SIZE];
	uint32_t test_time;

	static struct option longopts[] = {
			{"help", no_argument, NULL, 'h' },
			{"server", no_argument, NULL, 's' },
			{"client", no_argument, NULL, 'c' },
			{"port", required_argument, NULL, 'p'},
			{"address", required_argument, NULL, 'a'},
			{"time", required_argument, NULL, 't'},
	};

	while ((flag = getopt_long(argc, argv, "hscp:a:t:", longopts, NULL)) != -1) {
		switch (flag) {
		case 's':
			new_test->role = SERVER;
			tnet_debug("%s", "Server mode is set");
			break;

		case 'c':
			new_test->role = CLIENT;
			tnet_debug("%s", "Client mode is set");
			break;

		case 'p':
			portno = atoi(optarg);
			if (!tnet_validate_port_number(portno)) {
				return false;
			}
			new_test->port_no = portno;
			tnet_debug("%s %d", "Port number set:", portno);
			break;

		case 'a':
			strncpy(address_parameter, optarg, TNET_IP_ADDRESS_BUFFER_SIZE);
			if (!tnet_validate_ip_address(new_test, address_parameter)) {
				return false;
			}
			tnet_debug("%s %s", "IP address set:", address_parameter);
			break;

		case 't':
			test_time = atoi(optarg);
			if (!tnet_validate_test_duration_time(test_time)) {
				return false;
			}
			new_test->test_duration = test_time;
			tnet_debug("%s %d", "Test duration set to: ", test_time);
			break;

		case 'h':
		default:
			printf("%s","\nHelp:\n");
			break;
		}
	}

	tnet_validate_aguments_by_mode(new_test);

	return true;
}

/*### static methods ###*/

static bool tnet_validate_port_number(int32_t port_number) {
	if (port_number < TNET_MIN_PORT_NUMBER || port_number > TNET_MAX_PORT_NUMBER) {
		tnet_error("%s", "Invalid port number");
		return false;
	}

	tnet_debug("%s %d", "Valid port number:", port_number);
	return true;
}

static bool tnet_validate_ip_address(struct tnet_new_test* new_test, char* ip_addr) {

	in_addr_t ip_address;

	if ((ip_address = inet_addr(ip_addr)) < 0) {
		tnet_error("%s", "Invalid IP address");
		return false;
	}

	new_test->ip_address = ip_address;

	return true;
}

static bool tnet_validate_test_duration_time(uint32_t test_duration_time) {

	if (MAX_TEST_DURATION_TIME > test_duration_time) {
		tnet_error("%s %d [s]", "Set test time longer than: ", MAX_TEST_DURATION_TIME);
		return false;
	}

	return true;
}

static bool tnet_validate_aguments_by_mode(struct tnet_new_test* new_test) {

}
