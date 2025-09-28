cmake_minimum_required(VERSION 4.0)
project(erasmoOnichan)

set(CMAKE_CXX_STANDARD 20)

add_executable(erasmoOnichan main.cpp
        bibliotecas/funciones.cpp
        bibliotecas/funciones.h
        bibliotecas/utils.h)
