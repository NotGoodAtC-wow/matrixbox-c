cmake_minimum_required(VERSION 3.22)
project(matrixlab C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# library
add_library(matrixlab STATIC
        src/matrix.c
        include/matrix.h
        src/matrix.c
        src/main.c
)
target_include_directories(matrixlab PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# demo
add_executable(matrixlab_demo src/main.c)
target_link_libraries(matrixlab_demo PRIVATE matrixlab)

# tests
enable_testing()
add_executable(test_matrix tests/test_matrix.c
        tests/test_matrix.c)
target_link_libraries(test_matrix PRIVATE matrixlab)
add_test(NAME test_matrix COMMAND test_matrix)
add_executable(test_ops tests/test_ops.c
        tests/test_ops.c)
target_link_libraries(test_ops PRIVATE matrixlab)
add_test(NAME test_ops COMMAND test_ops)
# linuxproof
if(UNIX AND NOT APPLE)
    target_link_libraries(test_matrix PRIVATE m)
    target_link_libraries(test_ops    PRIVATE m)
    target_link_libraries(matrixlab_demo PRIVATE m)
endif()
if(UNIX AND NOT APPLE)
    target_link_libraries(test_matrix PRIVATE m)
    target_link_libraries(test_ops    PRIVATE m)
    target_link_libraries(matrixlab_demo PRIVATE m)
endif()
# optimized for C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
add_executable(test_mul tests/test_mul.c
        tests/test_mul.c)
target_link_libraries(test_mul PRIVATE matrixlab)
add_test(NAME test_mul COMMAND test_mul)
