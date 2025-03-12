cmake_minimum_required(VERSION 3.25)
project(ElPricesWebServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH "/usr/lib/cmake/Crow")
find_package(Crow CONFIG REQUIRED)

add_library(ElPricesWebServer
        ElPricesWebServerController.cpp
        include/ElPricesWebServer/ElPricesWebServerController.h
        include/ElPricesWebServer/ServePoint.h
        include/ElPricesWebServer/EndPoint.h
        include/ElPricesWebServer/IElPricesWebServer.h
        )

target_link_libraries(ElPricesWebServer PUBLIC Utility)
target_include_directories(ElPricesWebServer PUBLIC include)