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
#include "tnet_error.h"
#include "tnet_debug.h"

#include "tnet_arguments_parser.h"

#define TNET_MAX_PORT_NUMBER	65535
#define TNET_MIN_PORT_NUMBER	1

static bool tnet_validate_port_number(int32_t port_number);

bool tnet_parse_arguments(struct tnet_new_test* new_test, int32_t argc, char **argv) {

	int flag;
	int32_t portno;

	static struct option longopts[] = {
			{"server", no_argument, NULL, 's' },
			{"client", no_argument, NULL, 'c' },
			{"port", required_argument, NULL, 'p'},
			/*{"address", required_argument, NULL, 'a'},*/
	};

	while ((flag = getopt_long(argc, argv, "scp:", longopts, NULL)) != -1) {
		switch (flag) {
		case 's':
			new_test->role = SERVER;
			break;

		case 'c':
			new_test->role = CLIENT;
			break;

		case 'p':
			portno = atoi(optarg);
			if (!tnet_validate_port_number(portno)) {
				return false;
			}
			new_test->port_no = portno;
			tnet_debug("%s %d", "Port number set:", portno);
			break;
		}
	}

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
