cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_C_STANDARD 11)
project (TouchstoNet)
add_executable(TouchstoNet.x86
../src/main.c
../src/tnet_arguments_parser.c
../src/tnet_create_server.c
../src/tnet_create_client.c
../src/tnet_error.c
../src/tnet_debug.c
../src/tnet_new_test.c
)
