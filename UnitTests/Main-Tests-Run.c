#include "TouchstoNetTests/TouchstoNet-Settings-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Time-Counter-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Engine-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Instance-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Socket-Connection-Tests.c"

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
/*    RUN_TEST(set_callback_and_callback_function_is_called_after_2s_timeout);
    RUN_TEST(set_timeout_2s_and_set_time_is_elapsed);
    RUN_TEST(set_longer_timeout_14s_and_set_time_is_elapsed);
    RUN_TEST(start_counter_for_14_seconds_and_stop_it_after_5_seconds);
    RUN_TEST(start_touchstone_engine_and_true_returned);
    RUN_TEST(start_and_stop_touchstone_engine_and_true_returned);
    RUN_TEST(call_settings_get_role_and_role_is_returned);
    RUN_TEST(call_settings_get_port_number_and_port_number_is_returned);
    RUN_TEST(call_settings_get_ip_address_and_ip_address_is_returned);
    RUN_TEST(call_settings_get_test_duration_and_test_duration_is_returned);
    RUN_TEST(call_set_role_with_server_mode_and_server_mode_is_set);
    RUN_TEST(call_set_role_with_server_mode_and_true_is_returned);
    RUN_TEST(call_set_role_with_client_mode_and_server_mode_is_set);
    RUN_TEST(call_set_role_with_client_mode_and_true_is_returned);
    RUN_TEST(try_call_set_role_with_invalid_mode_and_false_is_returned);
    RUN_TEST(call_set_port_number_and_port_number_is_set);
    RUN_TEST(call_set_port_number_and_true_is_returned);
    RUN_TEST(try_set_port_number_with_invalid_to_big_value_and_false_is_returned);
    RUN_TEST(try_set_port_number_with_invalid_negative_value_and_false_is_returned);
    RUN_TEST(call_set_port_number_with_max_value_and_port_number_is_set);
    RUN_TEST(call_set_port_number_with_min_value_and_port_number_is_set);
    RUN_TEST(call_set_ip_address_with_valid_address_and_true_is_returned);
    RUN_TEST(call_set_ip_address_with_invalid_address_and_false_is_returned);
    RUN_TEST(call_set_test_duration_value_and_test_duration_is_set);
    RUN_TEST(call_set_test_duration_value_and_true_is_returned);
    RUN_TEST(call_set_test_duration_with_max_value_and_max_duration_is_set);
    RUN_TEST(call_set_test_duration_with_max_value_and_true_is_returned);
    RUN_TEST(call_set_test_duration_with_min_value_and_min_duration_is_set);
    RUN_TEST(call_set_test_duration_with_min_value_and_true_is_returned);
    RUN_TEST(call_set_test_duration_with_invalid_max_value_and_false_is_returned);
    RUN_TEST(call_set_test_duration_with_invalid_min_value_and_false_is_returned);

    RUN_TEST(inject_settings_to_instance_with_value_and_the_value_in_instance_is_the_same);
    RUN_TEST(inject_settings_to_instance_and_it_is_successful_and_true_returned);
    RUN_TEST(try_inject_null_pointer_of_settings_to_instance_and_false_returned);
    RUN_TEST(try_to_start_instance_with_null_pointer_of_settings_to_instance_and_false_returned);
    RUN_TEST(try_to_start_instance_without_injeted_settings_and_false_returned);
    RUN_TEST(start_instance_in_client_mode_and_it_is_successful_then_true_returned);
    RUN_TEST(start_instance_in_server_mode_and_it_is_successful_then_true_returned);
    RUN_TEST(stop_instance_in_client_mode_and_it_is_successful_then_true_returned);
    RUN_TEST(stop_instance_in_server_mode_and_it_is_successful_then_true_returned);*/

    RUN_TEST(start_client_server_connection_and_stop_them_after_5s);
    return UNITY_END();
}
