cmake_minimum_required(VERSION 3.22)
project(matrixbox C)

# --- Language / warnings ---
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- Library ---
add_library(matrixlab STATIC
        src/matrix.c
        src/matrix_io.c
        include/matrix_io.h
)
target_include_directories(matrixlab PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# --- Demo (optional; собирается, если есть src/main.c) ---
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")
    add_executable(matrixlab_demo src/main.c)
    target_link_libraries(matrixlab_demo PRIVATE matrixlab)
endif()

# --- CLI (переименованный таргет; бинарник будет "matrixlab(.exe)") ---
add_executable(matrixlab_cli src/cli.c
        src/cli.c)
set_target_properties(matrixlab_cli PROPERTIES OUTPUT_NAME matrixlab)
target_link_libraries(matrixlab_cli PRIVATE matrixlab)
target_include_directories(matrixlab_cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# --- Tests ---
enable_testing()

add_executable(test_matrix tests/test_matrix.c)
target_link_libraries(test_matrix PRIVATE matrixlab)
add_test(NAME test_matrix COMMAND test_matrix)

add_executable(test_ops tests/test_ops.c)
target_link_libraries(test_ops PRIVATE matrixlab)
add_test(NAME test_ops COMMAND test_ops)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_mul.c")
    add_executable(test_mul tests/test_mul.c)
    target_link_libraries(test_mul PRIVATE matrixlab)
    add_test(NAME test_mul COMMAND test_mul)
endif()

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_gauss.c")
    add_executable(test_gauss tests/test_gauss.c)
    target_link_libraries(test_gauss PRIVATE matrixlab)
    add_test(NAME test_gauss COMMAND test_gauss)
endif()

# --- CLI tests ---
set(DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/data)

add_test(NAME cli_det
        COMMAND $<TARGET_FILE:matrixlab_cli> det ${DATA_DIR}/A2x2.txt)
# проверяем точную подстроку из вывода
set_tests_properties(cli_det PROPERTIES
        PASS_REGULAR_EXPRESSION "det: -2")

add_test(NAME cli_rank
        COMMAND $<TARGET_FILE:matrixlab_cli> rank ${DATA_DIR}/I3.txt)
set_tests_properties(cli_rank PROPERTIES
        PASS_REGULAR_EXPRESSION "rank: 3")

add_test(NAME cli_mul
        COMMAND $<TARGET_FILE:matrixlab_cli> mul ${DATA_DIR}/A2x3.txt ${DATA_DIR}/B3x2.txt)
# достаточно одного характерного ряда
set_tests_properties(cli_mul PROPERTIES
        PASS_REGULAR_EXPRESSION "58 64")

add_test(NAME cli_trans
        COMMAND $<TARGET_FILE:matrixlab_cli> trans ${DATA_DIR}/A2x3.txt)
# достаточно одной характерной пары
set_tests_properties(cli_trans PROPERTIES
        PASS_REGULAR_EXPRESSION "1 4")
