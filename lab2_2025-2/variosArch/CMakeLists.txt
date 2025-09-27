cmake_minimum_required(VERSION 4.0)
project(variosArch)

set(CMAKE_CXX_STANDARD 20)

add_executable(variosArch main.cpp
        bibliotecas/funciones.cpp
        bibliotecas/funciones.h
        bibliotecas/utils.h
)
