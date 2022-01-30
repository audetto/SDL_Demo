cmake_minimum_required(VERSION 3.10)
project(SDLDemo)

include(FindPkgConfig)

find_package(SDL2 REQUIRED)

pkg_search_module(GLES2 REQUIRED glesv2)

add_executable(sddemo
  main.cpp
  sdlrenderer.cpp
  glrenderer.cpp
  )

target_include_directories(sddemo PRIVATE
  ${SDL2_INCLUDE_DIRS}
  )

target_link_libraries(sddemo PRIVATE
  ${SDL2_LIBRARIES}
  ${GLES2_LIBRARIES}
  )
