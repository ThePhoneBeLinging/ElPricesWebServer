cmake_minimum_required(VERSION 3.25)
project(ElPricesWebServer)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(src)

add_subdirectory(dependencies/Utility)
add_subdirectory(dependencies/DatabaseAccessController)
add_subdirectory(example)