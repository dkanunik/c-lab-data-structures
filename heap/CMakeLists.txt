cmake_minimum_required(VERSION 3.27)

project(heap C)

set(C_STANDARD 11)
set(C_COMPILER_LAUNCHER "gcc")

include_directories(include)

set(UNITY_LIBRARY_PATH /usr/local/src/unity)

include_directories(${UNITY_LIBRARY_PATH})

set(SOURCE_FILES
        src/heap.c
        test/test_heap.c
)

set(UNITY_SOURCE_FILES
        ${UNITY_LIBRARY_PATH}/unity.c
)

# Define the executable
add_executable(heap ${SOURCE_FILES} ${UNITY_SOURCE_FILES})
