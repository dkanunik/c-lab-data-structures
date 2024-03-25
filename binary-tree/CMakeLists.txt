cmake_minimum_required(VERSION 3.27)

project(binary_tree C)

set(C_STANDARD 11)
set(C_COMPILER_LAUNCHER "gcc")

include_directories(include)

set(UNITY_LIBRARY_PATH /usr/local/src/unity)
set(TEST_UTILS_PATH ../_test_data_utils)

include_directories(${UNITY_LIBRARY_PATH})
include_directories(${TEST_UTILS_PATH})

set(SOURCE_FILES
        src/binary_tree.c
        test/test_binary_tree.c
)

set(UNITY_SOURCE_FILES
        ${UNITY_LIBRARY_PATH}/unity.c
)

set(TEST_UTILS_PATH
        ${TEST_UTILS_PATH}/data_utils.c
)

add_executable(binary_tree ${SOURCE_FILES} ${UNITY_SOURCE_FILES} ${TEST_UTILS_PATH})
