cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO /NODEFAULTLIB:libc.lib")

set(CMAKE_C_FLAGS "-m32")
set(CMAKE_CXX_FLAGS "-m32")

# set the project name
project(EX4 VERSION 1.0.0)

file(GLOB_RECURSE ALL_SOURCE   
${PROJECT_SOURCE_DIR}/src/*.c
${PROJECT_SOURCE_DIR}/src/*.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/src)

# 预定义变量引入
link_directories(${PROJECT_SOURCE_DIR}/../lib)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/..)

# add the executable
add_executable(${PROJECT_NAME} ${ALL_SOURCE})

target_link_libraries(${PROJECT_NAME} glut32.lib)     # 注意子工程名和库文件名之间以空格隔开

