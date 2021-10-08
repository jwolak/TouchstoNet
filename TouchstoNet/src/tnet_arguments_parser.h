/*
 * tnet_arguments_parser.h
 *
 *  Created on: 2021
 *      Author: Janusz Wolak
 */

/*-
 * Copyright (c) 2021 Janusz Wolak  
 * All rights reserved.
 *
 */
#ifndef SRC_TNET_ARGUMENTS_PARSER_H_
#define SRC_TNET_ARGUMENTS_PARSER_H_


#include <stdbool.h>
#include <stdint.h>

#include "tnet_new_test.h"


bool tnet_parse_arguments(struct tnet_new_test* new_test, int32_t argc, char **argv);



#endif /* SRC_TNET_ARGUMENTS_PARSER_H_ */
