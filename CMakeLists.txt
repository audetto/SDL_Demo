cmake_minimum_required(VERSION 3.10)
project(Demo)

find_package(SDL2 REQUIRED)

add_executable(Demo main.cpp)

target_include_directories(Demo PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(Demo PRIVATE ${SDL2_LIBRARIES})
