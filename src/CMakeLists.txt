cmake_minimum_required(VERSION 3.25)
project(ElPricesWebServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH "/usr/lib/cmake/Crow")
find_package(Crow CONFIG REQUIRED)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(ElPricesWebServer STATIC
        ElPricesWebServerController.cpp
        include/ElPricesWebServer/ElPricesWebServerController.h
        HistoricEntry.h
)

target_link_libraries(ElPricesWebServer PUBLIC Utility)
target_link_libraries(ElPricesWebServer PUBLIC DatabaseAccessController)
target_include_directories(ElPricesWebServer PUBLIC include)
target_link_libraries(ElPricesWebServer PRIVATE nlohmann_json)