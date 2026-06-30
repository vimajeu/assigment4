cmake_minimum_required(VERSION 4.2)
project(assigment4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(assigment4
        CheckListLine.cpp
        CheckListLine.h
        Line.h
        TextEditor.cpp
        TextEditor.h
        TextLine.cpp
        TextLine.h
        ContactInfoLine.cpp
        ContactInfoLine.h
        Text.cpp
        Text.h)
