cmake_minimum_required(VERSION 3.27)
project(linked_list C)

set(C_STANDARD 11)
set(C_COMPILER_LAUNCHER "gcc")

set(unity_LIBRARY_DIR /usr/local/lib)

include_directories(include)

set(SOURCE_FILES
        src/linked_list.c
        test/test_linked_list.c
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${TEST_DATA_UTILS} unity)
