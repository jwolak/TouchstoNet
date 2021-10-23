/*
 * main.c
 *
 *  Created on: 2021
 *      Author: Janusz Wolak
 */

/*-
 * Copyright (c) 2021 Janusz Wolak
 * All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

#include "tnet_arguments_parser.h"
#include "tnet_create_server.h"
#include "tnet_create_client.h"
#include "tnet_error.h"
#include "tnet_debug.h"

static jmp_buf sigend_jmp_buf;

static void __attribute__ ((noreturn)) sigend_handler(int sig)
{
	tnet_debug("%s %d %s", "Signal", sig, "catched");
    longjmp(sigend_jmp_buf, 1);
}

int main(int argc, char **argv) {

	struct tnet_new_test* new_test;

	tnet_catch_sigend(sigend_handler);
	if (setjmp(sigend_jmp_buf)){
		tnet_signal_handler(new_test);
	}

	if (!tnet_create_new_test(&new_test)) {
		perror("Create new test failed!");
	}

	do {
		if (!tnet_parse_arguments(new_test, argc, argv)) {
			tnet_error("%s", "Arguments parsing failed");
			break;
		}

		if (new_test->role == SERVER) {
			if (!tnet_create_pid_file(new_test)) {
				tnet_debug("%s", "Create pid file failed");
				break;
			}

			if (!tnet_create_server(new_test)) {
				tnet_error("%s", "Create server failed");
				tnet_delete_pid_file(new_test);
				break;
			}

			tnet_delete_pid_file(new_test);

		}

		if (new_test->role == CLIENT) {
			if (!tnet_create_pid_file(new_test)) {
				tnet_debug("%s", "Create pid file failed");
				break;
			}

			if (!tnet_create_client(new_test)) {
				tnet_error("%s", "Create client failed");
				tnet_delete_pid_file(new_test);
				break;
			}

			tnet_delete_pid_file(new_test);
		}
	} while(false);

	if (!tnet_free_new_test(new_test))
		tnet_error("%s", "Free new test failed!");

    return 0;
}
