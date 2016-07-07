include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SRC "*.[ch]pp")
file(GLOB_RECURSE HEADERS "*.h")

add_library(json SHARED ${SRC} ${HEADERS})
add_library(json_static STATIC ${SRC} ${HEADERS})

#set_target_properties(json PROPERTIES  LINK_FLAGS "-Wl,--no-undefined")
set_target_properties(json_static PROPERTIES OUTPUT_NAME "json" LINK_FLAGS "-static -libgcc -static-libstdc++ -Wl,--no-undefined")

#防止构建库时自动清理其他库
set_target_properties(json PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(json_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)


#以下设置可以利用 cmake -D CMAKE_INSTALL_PREFIX=/usr ..进行配置
#安装执行文件/库文件
install(TARGETS json_static json
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
#安装普通文件
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/bin2ascii.h DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson DESTINATION include		#将rapidjson和sign目录安装到<prefix>/include下
		PATTERN "src"										#但不包括src目录
		PATTERN "rapidjson/*"						#过滤文件
		PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ)		#将rapidjson和sign下的所有文件指定权限为OWNER_WRITE OWNER_READ GROUP_READ