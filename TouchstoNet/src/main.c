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

#include "LoggerC.h"

static jmp_buf sigend_jmp_buf;

static void __attribute__ ((noreturn)) sigend_handler(int sig)
{
	/*tnet_debug("%s %d %s", "Signal", sig, "caught");*/
    longjmp(sigend_jmp_buf, 1);
}

int main(int argc, char **argv) {

  SET_LOG_LEVEL(DEBUG);
  SET_LOG_LOGGER_OUTPUT(CONSOLE_AND_FILE);

/*	tnet_catch_sigend(sigend_handler);
	if (setjmp(sigend_jmp_buf)){
		tnet_signal_handler(new_test);
	}*/

    return 0;
}
