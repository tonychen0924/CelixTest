cmake_minimum_required (VERSION 3.2)

set(project_name PLC2Bundle)
set(CMAKE_CXX_STANDARD 17)

project(${project_name})

# 引入celix外部依赖包(否则找不到add_celix_bundle)
find_package(Celix REQUIRED)

# SERVICE_EXAMPLE_API标记是否被引用过来避免重复引用导致cmake编译报错
if(NOT SERVICE_EXAMPLE_API)
    add_library(ServiceExamplesApi INTERFACE)
    target_include_directories(ServiceExamplesApi INTERFACE api)
    # 将条件变量设置为已引用
    set(SERVICE_EXAMPLE_API TRUE CACHE INTERNAL "")
endif()

# 头文件寻找目录
include_directories(include)
include_directories(../interface)
include_directories(../implement)
include_directories(../consumer)

# 源文件目录
aux_source_directory(src PROJECT_SRC_DIR)

# 生成bundles
add_celix_bundle(${project_name}
    SOURCES
        ${PROJECT_SRC_DIR}
)

# 生成container
# add_celix_container(MyContainer
#     CXX
#     BUNDLES
#         Celix::ShellCxx
#         Celix::shell_tui
#         ${project_name}
# )