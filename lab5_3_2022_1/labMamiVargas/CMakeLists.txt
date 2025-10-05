cmake_minimum_required(VERSION 4.0)
project(labMamiVargas)

set(CMAKE_CXX_STANDARD 20)

add_executable(labMamiVargas main.cpp
        Bibliotecas/funciones.cpp
        Bibliotecas/funciones.h
        Bibliotecas/utils.h)
