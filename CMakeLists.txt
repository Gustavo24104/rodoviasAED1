cmake_minimum_required(VERSION 3.27)
project(Rodovias_AED1 C)

set(CMAKE_C_STANDARD 23)

add_executable(Rodovias_AED1 main.c
        Rodovias.h
        Rodovias.c
        Rodovias.h
        cidades.c
        cidades.h)
