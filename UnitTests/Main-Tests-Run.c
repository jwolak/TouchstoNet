#include "TouchstoNetTests/TouchstoNet-Settings-Tests.c"

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
    return UNITY_END();
}
