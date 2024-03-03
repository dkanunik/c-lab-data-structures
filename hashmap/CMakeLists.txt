cmake_minimum_required(VERSION 3.27)

project(hashmap C)

set(C_STANDARD 11)
set(c_COMPILER_LAUNCHER "gcc")

include_directories(include)

set(UNITY_LIBRARY_PATH /home/qa3/Projects/Unity/src)

include_directories(${UNITY_LIBRARY_PATH})

set(SOURCE_FILES
    src/hashmap.c
    test/test_suite.c
        src/hashmap.c
)

set(UNITY_SOURCE_FILES
    ${UNITY_LIBRARY_PATH}/unity.c
)

# Define the executable
add_executable(hashmap ${SOURCE_FILES} ${UNITY_SOURCE_FILES})
