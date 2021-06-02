cmake_minimum_required(VERSION 3.16)
project(L9733-Driver C)
add_definitions(-std=c99)
add_executable(driver main.c L9733.c)