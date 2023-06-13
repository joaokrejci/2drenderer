cmake_minimum_required(VERSION 3.12)
project("tests")

add_executable(dynamic_array_test dynamic_array_test.c ../src/dynamic_array.c)

target_link_libraries(dynamic_array_test PUBLIC check)