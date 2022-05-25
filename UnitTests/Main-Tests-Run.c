#include "TouchstoNetTests/TouchstoNet-Settings-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Time-Counter-Tests.c"

#include "unity.h"

#include "LoggerC.h"

void tearDown(void) {
  //remove("logs.log");
}

void setUp(void) {
    // set stuff up here
}

int main(void) {

  SET_LOG_LEVEL(DEBUG);
  SET_LOG_LOGGER_OUTPUT(CONSOLE_AND_FILE);

    UNITY_BEGIN();
    RUN_TEST(get_role_test);
    RUN_TEST(set_callback_and_callback_function_is_called_after_timeout);
    RUN_TEST(set_timeout_and_set_time_is_elapsed);
    RUN_TEST(set_longer_timeout_and_set_time_is_elapsed);
    RUN_TEST(thread);
    return UNITY_END();
}
