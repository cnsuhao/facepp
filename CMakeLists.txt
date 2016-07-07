project(FaceppApi)
cmake_minimum_required(VERSION 2.8)		#设置cmake支持的最低版本#设置C++编译选项（CMAKE_CXX_FLAGS）

MESSAGE(STATUS "This is CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR})  
#设置C++编译选项（CMAKE_CXX_FLAGS）
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -g3  -fPIC -Wall -Wextra -Wno-unused-variable -Wno-unused-local-typedefs -Wno-unused-parameter -rdynamic -fpermissive")

include(libs/CMakeLists.txt)

#添加头文件搜索路径
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/http)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/faceppApi)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

