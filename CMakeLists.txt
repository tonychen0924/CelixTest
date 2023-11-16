#container cmakelist
cmake_minimum_required (VERSION 3.22)

set(CMAKE_C_COMPILER gcc)  # 使用 gcc 编译器
set(CMAKE_CXX_COMPILER g++)  # 使用 g++ 编译器

project(containerMain)

find_package(Celix REQUIRED)

add_subdirectory(command_provider_bundle)
add_subdirectory(command_consumer_bundle)
# 只编译不加载用于测试使用
add_subdirectory(test_bundle)

add_celix_container(MyContainer
BUNDLES
    Celix::shell
    Celix::shell_wui
    Celix::shell_tui
    CommandProviderBundle
    CommandConsumerBundle
)