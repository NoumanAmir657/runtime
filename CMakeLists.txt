cmake_minimum_required(VERSION 3.10)
project(Runtime C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# For CTest Integration
enable_testing()

option(RUNTIME_USE_DEBUG_ALLOCATOR "Enable the debug allocator with logging" OFF)

add_library(runtime_lib
    src/allocator.c
    src/allocator_debug.c
)

target_include_directories(runtime_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(RUNTIME_USE_DEBUG_ALLOCATOR)
    target_compile_definitions(runtime_lib PUBLIC
       ALLOCATOR_SYSTEM_CTL=allocator_debug_ctl
    )
endif()

add_executable(runner tools/main.c)
target_link_libraries(runner PRIVATE runtime_lib)

# --- Tests ---
add_executable(allocator_test tests/allocator_test.c)
target_include_directories(allocator_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(allocator_test PRIVATE runtime_lib)
add_test(NAME allocator_test COMMAND allocator_test)
