cmake_minimum_required(VERSION 3.20)

project(CPP_Assignment_07)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/permissive-)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(3rd-party)
add_subdirectory(particle)
