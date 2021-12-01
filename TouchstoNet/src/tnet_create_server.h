/*
 * tnet_create_server.h
 *
 *  Created on: 2021
 *      Author: Janusz Wolak
 */

/*-
 * Copyright (c) 2021 Janusz Wolak  
 * All rights reserved.
 *
 */
#ifndef SRC_TNET_CREATE_SERVER_H_
#define SRC_TNET_CREATE_SERVER_H_

#include <stdbool.h>
#include <stdint.h>

#include "tnet_new_test.h"

bool tnet_create_server(struct tnet_new_test* new_test);

bool tnet_server_listen(struct tnet_new_test* new_test);

bool tnet_net_announce(int32_t domain, int32_t proto, const char *local, const char *bind_dev, int32_t port);


#endif /* SRC_TNET_CREATE_SERVER_H_ */
