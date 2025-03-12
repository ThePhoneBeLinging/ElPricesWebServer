cmake_minimum_required(VERSION 3.28)
project(ElPricesWebServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH "/usr/lib/cmake/Crow")
find_package(Crow CONFIG REQUIRED)

add_executable(ElPricesWebServer
        main.cpp
        ElPricesWebServerController.cpp
        ElPricesWebServerController.h
        )