cmake_minimum_required(VERSION 3.27)
project(Rodovias_AED1 C)

set(CMAKE_C_STANDARD 23)

add_executable(Rodovias_AED1 main.c
        headers/Rodovias.h
        headers/Rodovias.c
        headers/Rodovias.h
        headers/cidades.c
        headers/cidades.h
        headers/Caminhos.c
        headers/Caminhos.h)
