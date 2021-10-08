cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11)
project (UnitTestsOfTouchstoNet) 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Link runTests with what we want to test and the GTest and pthread library
add_executable(UnitTestsOfTouchstoNet.x86 ../Main-Tests-Run.cpp)

target_link_libraries(UnitTestsOfTouchstoNet.x86 ${GTEST_LIBRARIES} pthread)
target_link_libraries(UnitTestsOfTouchstoNet.x86 ${GTEST_LIBRARIES} gmock)
