cmake_minimum_required(VERSION 3.21)
project(wet2mivneiNirNiz)

set(CMAKE_CXX_STANDARD 14)

add_executable(wet2mivneiNirNiz main.cpp
        avl_rank.h
        Team.cpp
        Team.h
        worldcup23a2.cpp
        worldcup23a2.h
        wet2util.h
        Player_UnionFind_Node.cpp
        Player_UnionFind_Node.h
        Player.h
        Player.cpp
        HashTable.h
        HashTable.cpp
        List.cpp
        List.h
        main23a2.cpp)
