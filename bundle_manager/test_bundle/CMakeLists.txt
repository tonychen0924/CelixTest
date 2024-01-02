cmake_minimum_required (VERSION 3.2)

project(TestBundle)

set(CMAKE_CXX_STANDARD 17)

find_package(Celix REQUIRED)

include_directories(include)

add_celix_bundle(TestBundle
    SOURCES src/TestBundle.cpp
)