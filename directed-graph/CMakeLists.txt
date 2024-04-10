cmake_minimum_required(VERSION 3.27)

project(directed_graph C)

set(C_STANDARD 11)
set(C_COMPILER_LAUNCHER "gcc")

include_directories(include)

set(UNITY_LIBRARY_PATH /usr/local/src/unity)
set(TEST_UTILS_PATH ../_test_data_utils)

include_directories(${UNITY_LIBRARY_PATH})
include_directories(${TEST_UTILS_PATH})

set(SOURCE_FILES
        src/directedGraph.c
        src/edge.c
        src/vertex.c
)

set(UNITY_SOURCE_FILES
        ${UNITY_LIBRARY_PATH}/unity.c
)

set(TEST_UTILS_PATH
        ${TEST_UTILS_PATH}/data_utils.h
        include/directedGraph.h
        test/testDirectedGraph.c
)

add_executable(directed_graph ${SOURCE_FILES} ${UNITY_SOURCE_FILES} ${TEST_UTILS_PATH})
