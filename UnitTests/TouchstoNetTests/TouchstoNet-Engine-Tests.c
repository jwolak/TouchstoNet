/*
 * TouchstoNet-Engine-Tests.c
 *
 *  Created on: 2022
 *      Author: Janusz Wolak
 */

/*-
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Janusz Wolak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */


#include "unity.h"

#include "../../TouchstoNet/src/TouchstoNet-Engine.c"
#include "../../TouchstoNet/src/TouchstoNet-Agruments-Parser.c"

void *start_wrapper(void *arg) {

  char* kTestProgramName = (char*)"TestAppName";
  uint32_t kNumberOfArgumentsSetToOne   = 1;
  char* kEmptyCommandLineArgument[] = {kTestProgramName};
  struct TouchstoNetEngine* tnet_engine = (struct TouchstoNetEngine*)arg;

  tnet_engine->start(tnet_engine, kNumberOfArgumentsSetToOne, kEmptyCommandLineArgument);
}

void EngineTests_start_and_stop_touchstone_engine_and_true_returned() {

  pthread_t thread_id;
  struct TouchstoNetEngine tnet_engine = TouchstoNetEngine.new();

  pthread_create( &thread_id, NULL, start_wrapper, &tnet_engine);
  sleep(2);

  TEST_ASSERT_TRUE(tnet_engine.stop(&tnet_engine));
  pthread_cancel(thread_id);

}
