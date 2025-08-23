cmake_minimum_required(VERSION 3.15.0)
project(KneeboardLib LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(KneeboardLib SHARED src/kneeboard.cpp)

target_include_directories(KneeboardLib PUBLIC include)