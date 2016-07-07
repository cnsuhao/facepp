set(THIRD_PATH ${CMAKE_SOURCE_DIR}/libs)
message("THIRD_LIB_PATH = ${THIRD_PATH}")

macro(add_thirdparty_library DIR LIBNAME)
    include_directories(${DIR}/include)
    add_library(${LIBNAME} STATIC IMPORTED)
        set_property(TARGET ${LIBNAME} PROPERTY
                IMPORTED_LOCATION ${DIR}/lib/lib${LIBNAME}.a)
    message("add lib: ${LIBNAME}")
endmacro(add_thirdparty_library)


#add_thirdparty_library(${THIRD_PATH}/openssl ssl)
#add_thirdparty_library(${THIRD_PATH}/openssl crypto)
add_thirdparty_library(${THIRD_PATH}/curl curl)

#add_thirdparty_library(${THIRD_PATH}/iniParser iniparser)
#add_thirdparty_library(${THIRD_PATH}/sqlite3 sqlite3)
add_thirdparty_library(${THIRD_PATH}/zlog zlog)
add_thirdparty_library(${THIRD_PATH}/jsoncpp jsoncpp)