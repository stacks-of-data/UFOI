cmake_minimum_required(VERSION "2.9")

project("ufoi")
include_directories("includes")
add_library("${PROJECT_NAME}" STATIC "srcs/ufoi.cpp")