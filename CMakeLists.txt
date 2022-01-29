cmake_minimum_required(VERSION 3.10)
project(SDLDemo)

find_package(SDL2 REQUIRED)

add_executable(sddemo
  main.cpp
  sdlrenderer.cpp
  common.cpp
  )

target_include_directories(sddemo PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(sddemo PRIVATE ${SDL2_LIBRARIES})
