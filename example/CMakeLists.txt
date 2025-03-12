cmake_minimum_required(VERSION 3.28)
project(EXAMPLE_ElPricesWebServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(EXAMPLE_ElPricesWebServer
        main.cpp
        )

target_link_libraries(EXAMPLE_ElPricesWebServer PUBLIC ElPricesWebServer)