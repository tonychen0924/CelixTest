cmake_minimum_required(VERSION 3.22)

project(CommandConsumerBundle)

set(CMAKE_C_COMPILER gcc)  # 使用 gcc 编译器
set(CMAKE_CXX_COMPILER g++)  # 使用 g++ 编译器

# 引入celix外部依赖包(否则找不到add_celix_bundle)
find_package(Celix REQUIRED)

# SERVICE_EXAMPLE_API标记是否被引用过来避免重复引用导致cmake编译报错
if(NOT SERVICE_EXAMPLE_API)
    add_library(ServiceExamplesApi INTERFACE)
    target_include_directories(ServiceExamplesApi INTERFACE api)
    # 将条件变量设置为已引用
    set(SERVICE_EXAMPLE_API TRUE CACHE INTERNAL "")
endif()

# Pou的头文件存放
include_directories(include)
include_directories(../interface)
include_directories(../implement)

aux_source_directory(./src PROJECT_SRC_DIR)

add_celix_bundle(CommandConsumerBundle
        VERSION 1.0.0
        SOURCES ${PROJECT_SRC_DIR}
)
target_link_libraries(CommandConsumerBundle PRIVATE ServiceExamplesApi)

# 生成container
# add_celix_container(MyContainer
#     CXX
#     BUNDLES
#         Celix::ShellCxx
#         Celix::shell_tui
#         CommandConsumerBundle
# )