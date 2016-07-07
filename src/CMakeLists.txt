MESSAGE(STATUS "This is CMAKE_CURRENT_SOURCE_DIR = "${CMAKE_CURRENT_SOURCE_DIR})  

file(GLOB_RECURSE SRC "*.[ch]pp")
file(GLOB_RECURSE HEADERS "*.h")

#编译出一个可执行文件且命名为faceIdentify
set(TARGET_NAME faceTest)
add_executable(${TARGET_NAME} ${SRC} ${HEADERS})


#添加编译可执行程序所需要的链接库、如果有多个中间用空格隔开  
#第一个参数是可执行程序名称，第二个开始是依赖库  iniparser curl
#在这里根据名字XXX去寻找libXXX.a文件 
target_link_libraries(${TARGET_NAME}    curl ssl crypto
                                        jsoncpp
										pthread
										zlog                                      
										dl rt
                                        )
set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++ -Wl,--no-undefined")

#把二进制执行文件指定到工程的bin目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

#enable_testing()