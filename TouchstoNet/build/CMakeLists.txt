cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_C_STANDARD 11)
project (TouchstoNet)
set (SOURCE_FILES_DIR "../src")

include_directories(${CMAKE_SOURCE_DIR}/../../EquinoxC-Logger/EquinoxC-Logger/src)
link_directories(${CMAKE_SOURCE_DIR}/../../EquinoxC-Logger/EquinoxC-Logger/build)

add_executable(TouchstoNet.x86
${SOURCE_FILES_DIR}/main.c
${SOURCE_FILES_DIR}/TouchstoNet-Agruments-Parser.c
${SOURCE_FILES_DIR}/TouchstoNet-Settings.c
)

target_link_libraries(TouchstoNet.x86 libEquinoxCLogger.a)
target_link_libraries(TouchstoNet.x86 pthread)
