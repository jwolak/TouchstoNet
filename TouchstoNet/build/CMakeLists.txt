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
${SOURCE_FILES_DIR}/TouchstoNet-Engine.c
${SOURCE_FILES_DIR}/TouchstoNet-Time-Counter.c
${SOURCE_FILES_DIR}/TouchstoNet-Instance.c
${SOURCE_FILES_DIR}/TouchstoNet-Server.c
${SOURCE_FILES_DIR}/TouchstoNet-Client.c
${SOURCE_FILES_DIR}/TouchstoNet-Socket.c
${SOURCE_FILES_DIR}/TouchstoNet-Socket-Address.c
${SOURCE_FILES_DIR}/TouchstoNet-Socket-Connection.c
${SOURCE_FILES_DIR}/TouchstoNet-Message-Model.c
#${SOURCE_FILES_DIR}/
#${SOURCE_FILES_DIR}/
#${SOURCE_FILES_DIR}/
)

target_link_libraries(TouchstoNet.x86 libEquinoxCLogger.a)
target_link_libraries(TouchstoNet.x86 pthread)
