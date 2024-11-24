cmake_minimum_required(VERSION 3.26)
project(TG_projet C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(TG_projet
        main.c
        Reseau.h
)
