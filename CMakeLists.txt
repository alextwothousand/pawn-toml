cmake_minimum_required(VERSION 3.17)
project(pawn_toml C)

set(CMAKE_C_STANDARD 11)

add_library(pawn_toml SHARED library.c library.h)