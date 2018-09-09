cmake_minimum_required(VERSION 3.9)
project(FinalProject)

set(CMAKE_CXX_STANDARD 11)

add_executable(FinalProject
        FileController.c
        FileController.h
        GameBoardClass.c
        GameBoardClass.h
        GameManager.c
        GameManager.h
        InputController.c
        InputController.h
        main.c
        utils.c
        utils.h LinkedList.c LinkedList.h Stack.c Stack.h exhaustive.c exhaustive.h)
