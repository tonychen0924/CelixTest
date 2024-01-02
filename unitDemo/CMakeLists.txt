cmake_minimum_required(VERSION 3.22)

project(test)

#set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# 引入celix外部依赖包(否则找不到add_celix_bundle)
find_package(Celix REQUIRED)
        
add_library(ServiceExamplesApi INTERFACE)
target_include_directories(ServiceExamplesApi INTERFACE api)

include_directories(interface)
include_directories(implement)

include_directories(ctrl/include)
aux_source_directory(ctrl/src CTRL_PROJECT_SRC_DIR)
add_celix_bundle(PlcCtrlBundle
        VERSION 1.0.0
        SOURCES ${CTRL_PROJECT_SRC_DIR}
)
target_link_libraries(PlcCtrlBundle PRIVATE ServiceExamplesApi)

include_directories(rte/include)
aux_source_directory(rte/src RTE_PROJECT_SRC_DIR)
add_celix_bundle(RteBundle
        VERSION 1.0.0
        SOURCES ${RTE_PROJECT_SRC_DIR}
)
target_link_libraries(RteBundle PRIVATE ServiceExamplesApi)

# 生成container
add_celix_container(MyContainer
    CXX
    BUNDLES
        Celix::ShellCxx
        Celix::shell_tui
        PlcCtrlBundle
        RteBundle
)