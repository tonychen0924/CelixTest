cmake_minimum_required (VERSION 3.2)

project(LiterteDemoBundle)

set(CMAKE_CXX_STANDARD 17)

find_package(Celix REQUIRED)

include_directories(include)

add_celix_bundle(LiterteDemoBundle
    SOURCES src/LiterteDemoBundle.cpp
)

add_celix_container(MyContainer
    CXX
    BUNDLES
        Celix::ShellCxx
        Celix::shell_tui
        LiterteDemoBundle
)