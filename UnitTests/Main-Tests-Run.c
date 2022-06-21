#include "TouchstoNetTests/TouchstoNet-Settings-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Time-Counter-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Engine-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Instance-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Socket-Connection-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Message-Model-Tests.c"
#include "TouchstoNetTests/TouchstoNet-Agruments-Parser-Tests.c"

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
/*  RUN_TEST(set_callback_and_callback_function_is_called_after_2s_timeout);
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
    RUN_TEST(stop_instance_in_server_mode_and_it_is_successful_then_true_returned);

    RUN_TEST(start_client_server_connection_and_stop_them_after_5s);

    RUN_TEST(MessageModelTest_prepare_message_with_size_128_bytes_and_true_returned);
    RUN_TEST(MessageModelTest_prepare_message_with_size_128_bytes_and_message_size_filed_is_set_to_128);
    RUN_TEST(MessageModelTest_prepare_message_with_invalid_max_size_and_false_returned);
    RUN_TEST(MessageModelTest_prepare_message_with_invalid_size_and_false_returned);
    RUN_TEST(MessageModelTest_prepare_message_with_size_128_bytes_and_buffer_has_128_bytes_allocated);
    RUN_TEST(MessageModelTest_prepare_message_with_test_content_and_buffer_content_is_the_same);
    RUN_TEST(MessageModelTest_prepare_message_with_size_128_bytes_and_get_msg_size_returns_size_128_bytes);

    RUN_TEST(AgrumentsParserTest_inject_settings_with_set_port_number_and_it_is_set_in_arguments_parser);
    RUN_TEST(AgrumentsParserTest_inject_settings_and_true_is_returned);
    RUN_TEST(AgrumentsParserTest_try_inject_settings_with_null_pointer_and_false_returned);
    RUN_TEST(AgrumentsParserTest_try_to_no_arguments_provide_and_false_returned);
    RUN_TEST(AgrumentsParserTest_provide_help_print_argument_and_true_returned);
    RUN_TEST(AgrumentsParserTest_provide_server_mode_argument_and_server_role_is_set);
    RUN_TEST(AgrumentsParserTest_no_role_provided_and_default_role_set_to_client_mode);
    RUN_TEST(AgrumentsParserTest_provide_client_mode_argument_and_client_role_is_set);
    RUN_TEST(AgrumentsParserTest_provide_valid_port_number_and_port_is_set);
    RUN_TEST(AgrumentsParserTest_try_set_invalid_zero_port_number_and_false_returned);
    RUN_TEST(AgrumentsParserTest_try_set_invalid_max_port_number_and_false_returned);
    RUN_TEST(AgrumentsParserTest_provide_valid_IP_address_and_IP_address_is_set);
    RUN_TEST(AgrumentsParserTest_provide_invalid_IP_address_and_false_is_returned);
    RUN_TEST(AgrumentsParserTest_provide_invalid_signs_in_IP_address_and_false_is_returned);
    RUN_TEST(AgrumentsParserTest_provide_valid_test_time_and_it_is_set);
    RUN_TEST(AgrumentsParserTest_provide_valid_test_time_and_true_is_returned);
    RUN_TEST(AgrumentsParserTest_provide_invalid_minimum_test_time_and_it_is_set);
    RUN_TEST(AgrumentsParserTest_provide_valid_minimum_test_time_and_it_is_set);
    RUN_TEST(AgrumentsParserTest_provide_valid_maximum_test_time_and_it_is_set);
    RUN_TEST(AgrumentsParserTest_provide_invalid_maximum_test_time_and_false_is_returned); */
    RUN_TEST(AgrumentsParserTest_provide_invalid_negative_test_time_and_false_is_returned);

/*    RUN_TEST(EngineTest_start_and_stop_touchstone_engine_and_true_returned);*/
    return UNITY_END();
}
