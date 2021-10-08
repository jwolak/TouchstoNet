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

#include "tnet_arguments_parser.h"

bool tnet_parse_arguments(struct tnet_new_test* new_test, int32_t argc, char **argv) {

	int flag;
	int portno;

	static struct option longopts[] = { { "server", no_argument, NULL, 's' }, {
			"client", no_argument, NULL, 'c' }, };

	while ((flag = getopt_long(argc, argv, "sc", longopts, NULL)) != -1) {
		switch (flag) {
		case 's':
			new_test->role = SERVER;
			break;

		case 'c':
			new_test->role = CLIENT;
			break;
		}
	}

	return true;
}
