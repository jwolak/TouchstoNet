cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_C_STANDARD 11)
project (TouchstoneNetTests)
include_directories(../UnityTestFramework/Unity/src)
link_directories(../UnityTestFramework/Unity)

include_directories(${CMAKE_SOURCE_DIR}/../../EquinoxC-Logger/EquinoxC-Logger/src)
link_directories(${CMAKE_SOURCE_DIR}/../../EquinoxC-Logger/EquinoxC-Logger/build)

add_executable(TouchstoneNetTests.x86 ../Main-Tests-Run.c)

target_link_libraries(TouchstoneNetTests.x86 libunity.a)
target_link_libraries(TouchstoneNetTests.x86 libEquinoxCLogger.a)