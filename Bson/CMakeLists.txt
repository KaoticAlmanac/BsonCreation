cmake_minimum_required(VERSION 3.8)
project(ToBson)


set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp stdafx.h)
add_executable(ToBson ${SOURCE_FILES})

find_package (libbson-1.0 1.7 REQUIRED)




add_library(lib libbson-1.7.0/src/bson/bson.c libbson-1.7.0/src/bson/bson.h)
message ("--   libbson-static found version \"${BSON_VERSION}\"")
message ("--   libbson-static include path \"${BSON_INCLUDE_DIRS}\"")
message ("--   libbson-static libraries \"${BSON_LIBRARIES}\"")
add_executable (main main.cpp stdafx.h)
target_include_directories (main PRIVATE ${BSON_INCLUDE_DIRS})
target_link_libraries (main PRIVATE ${BSON_LIBRARIES})
target_compile_definitions (main PRIVATE ${BSON_DEFINITIONS})

