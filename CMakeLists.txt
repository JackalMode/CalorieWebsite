cmake_minimum_required(VERSION 3.10)
project(CalorieTracker)

set(CMAKE_CXX_STANDARD 20)
add_executable(CalorieTracker
        main.cpp
        Food.cpp
        Food.h
        FoodDatabase.h
        FoodDatabase.cpp
        Menu.cpp
        Menu.h
        Journal.cpp
        Journal.h
        HtmlRend.cpp
        HtmlRend.h)
add_executable(test Test.cpp Food.cpp
        Food.h
        FoodDatabase.h
        FoodDatabase.cpp
        Menu.cpp
        Menu.h
        Journal.cpp
        Journal.h)