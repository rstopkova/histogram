cmake_minimum_required(VERSION 2.8)

project(code)
add_compile_options(-Wall -Wextra -std=c99 -Werror -g)
add_executable(${PROJECT_NAME} "main.c")
