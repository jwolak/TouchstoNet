/*
 * tnet_error.h
 *
 *  Created on: 2021
 *      Author: Janusz Wolak
 */

/*-
 * Copyright (c) 2021 Janusz Wolak  
 * All rights reserved.
 *
 */
#ifndef SRC_TNET_ERROR_H_
#define SRC_TNET_ERROR_H_

#include "tnet_new_test.h"

#define TIMESTAMP_FORMAT		"%c"
#define LOG_TIMESTAMP_LENGTH	100
#define LOG_MESSAGE_LENGTH		1000

char iperf_timestrerr[LOG_TIMESTAMP_LENGTH];

void tnet_error(const char *format, ...);


#endif /* SRC_TNET_ERROR_H_ */
