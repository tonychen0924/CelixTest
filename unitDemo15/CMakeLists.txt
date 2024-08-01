#container cmakelist
cmake_minimum_required (VERSION 3.22)

set(CMAKE_C_COMPILER gcc)  # 使用 gcc 编译器
set(CMAKE_CXX_COMPILER g++)  # 使用 g++ 编译器
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)

set(project_name ACEPhereRuntime)
project(${project_name})

find_package(Celix REQUIRED)

# 为了使得每个子项目都能单独编译，因此注释此内容
# add_library(ServiceExamplesApi INTERFACE)
# target_include_directories(ServiceExamplesApi INTERFACE api)

add_subdirectory(Pou)
add_subdirectory(PLC1)
add_subdirectory(PLC2)

add_celix_container(${project_name}
BUNDLES
    Celix::shell
    Celix::shell_wui
    Celix::shell_tui
    PouBundle
    PLC1Bundle
    PLC2Bundle
)