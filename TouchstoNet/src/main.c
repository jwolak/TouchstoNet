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
#include "TouchstoNet-Engine.h"

static jmp_buf sigend_jmp_buf;

static void __attribute__ ((noreturn)) sigend_handler(int sig)
{
    LOG_WARNING("%s%d%s", "Signal: ", sig, " caught");
    longjmp(sigend_jmp_buf, 1);
}

static void tnet_catch_sigend(void (*handler)(int))
{
#ifdef SIGINT
    signal(SIGINT, handler);
#endif
#ifdef SIGTERM
    signal(SIGTERM, handler);
#endif
#ifdef SIGHUP
    signal(SIGHUP, handler);
#endif
}

int main(int argc, char **argv) {

  SET_LOG_LEVEL(DEBUG);
  SET_LOG_LOGGER_OUTPUT(CONSOLE_AND_FILE);

  struct TouchstoNetEngine touchstonet_engine =  TouchstoNetEngine.new();

	tnet_catch_sigend(sigend_handler);
	if (setjmp(sigend_jmp_buf)){

		if (!touchstonet_engine.stop(&touchstonet_engine)) {
		  LOG_WARNING("%s", "Failed to stop TouchstoNet engine");
		}

		LOG_WARNING("%s", "TouchstoNet engine interrupted by user");
	}

  if (!touchstonet_engine.start(&touchstonet_engine, argc, argv)) {

    LOG_ERROR("%s", "Failed to start TouchstoNet engine");
    exit(1);
  } else {
    LOG_DEBUG("%s", "TouchstoNet run session successful");
  }


    return 0;
}
