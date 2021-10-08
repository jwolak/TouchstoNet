/*
 * tnet_debug.c
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
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "tnet_debug.h"


void tnet_debug(const char *format, ...) {

	va_list argp;
    char str[LOG_MESSAGE_LENGTH];
    time_t now;
    struct tm *ltm = NULL;
    char *ct = NULL;

	time(&now);
	ltm = localtime(&now);
	strftime(iperf_timestrerr_debug, sizeof(iperf_timestrerr_debug), TIMESTAMP_FORMAT, ltm);
	ct = iperf_timestrerr_debug;


    va_start(argp, format);
    vsnprintf(str, sizeof(str), format, argp);

/*		if (test && test->outfile && test->outfile != stdout) {
	    if (ct) {
		fprintf(test->outfile, "%s", ct);
	    }
	    fprintf(test->outfile, "tnet: %s\n", str);
	}
	else {*/
	    if (ct) {
		fprintf(stderr, "%s", ct);
	    }
	    fprintf(stderr, " [DEBUG]: %s\n", str);
	/*}*/
    va_end(argp);
}
