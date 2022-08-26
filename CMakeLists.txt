cmake_minimum_required(VERSION 3.22)
project(Trabalho_Grupo43)

set(CMAKE_CXX_STANDARD 14)

include_directories(Headers)

add_executable(Trabalho_Grupo43
        Headers/Edge.h
        Headers/Graph.h
        Headers/GraphKruskal.h
        Headers/GraphPrim.h
        Headers/Menu.h
        Headers/Node.h
        MIs/Edge.cpp
        MIs/Graph.cpp
        MIs/GraphKruskal.cpp
        MIs/GraphPrim.cpp
        MIs/Menu.cpp
        MIs/Node.cpp
        MIs/PrintDOT.cpp
        main.cpp)
