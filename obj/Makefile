#############################################################################
# Makefile  for building: 
# author:   sliang
# Project:  RobotService
# Template: app
# Command:  gcc g++
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options
PROJECTPATH   =${shell pwd}
CC            = gcc
CXX           = g++
CFLAGS        = -Wall
CXXFLAGS      = -pipe -std=gnu++0x -Wall -W -D_REENTRANT -fPIC 
INCPATH       = -I../include/libghttp-1.0.9 -I../include/common -I../include/sqlite3 -I../json_api -I../libs/iniparser-2.14 -I../common -I../include
DEL_FILE      = rm -f
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
LINK          = g++
LFLAGS        = -Wl,-z,origin -Wl,-rpath,\$$ORIGIN
LIBS          = -lpthread -lsqlite3 -L../libs/SQlite3_3.12.01 -lghttp -L../libs/libghttp-1.0.9 -ljson_linux-gcc-5.2.1_libmt -L../libs/jsoncpp
AR            = ar cqs
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files
		 
OBJECTS = server_core.o \
		server_robot.o \
		server_mobile.o \
		server_webServer.o \
		server_login.o \
		server_module.o \
		server_logs.o \
		tcputil.o \
		tcplistutil.o \
		httputil.o \
		json_access_api.o \
		json_frm_parse.o \
		dictionary.o \
		strlib.o \
		iniparser.o \
		common.o \
		debug.o \
		iniSystem.o \
		db_server_api.o \
		maintain_db.o
		

TARGET        = robotserver


first: all
####### Build rules

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

all: Makefile $(TARGET)


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)


distclean: clean 
	-$(DEL_FILE) $(TARGET)
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile

check: first
compiler_clean:

####### Compile

common.o: ../common/common.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o common.o ../common/common.c
	
debug.o: ../common/debug.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o debug.o ../common/debug.c
	
maintain_db.o: ../common/maintain_db.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o maintain_db.o ../common/maintain_db.c
	
server_core.o: ../server_core.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o server_core.o ../server_core.c
	
server_robot.o: ../server_robot.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o server_robot.o ../server_robot.c
	
server_mobile.o: ../server_mobile.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o server_mobile.o ../server_mobile.c
	
server_webServer.o: ../server_webServer.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o server_webServer.o ../server_webServer.c
	
server_login.o: ../server_login.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o server_login.o ../server_login.c
	
server_logs.o: ../server_logs.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o server_logs.o ../server_logs.c
	
tcputil.o: ../tcputil.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o tcputil.o ../tcputil.c
	
tcplistutil.o: ../tcplistutil.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o tcplistutil.o ../tcplistutil.c
	
httputil.o: ../http/httputil.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o httputil.o ../http/httputil.c
	
db_server_api.o: ../common/db_server_api.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o db_server_api.o ../common/db_server_api.c
	
######################################################################################
server_module.o: ../server_module.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o server_module.o ../server_module.cpp
	
json_access_api.o: ../json_api/json_access_api.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o json_access_api.o ../json_api/json_access_api.cpp
	
json_frm_parse.o: ../json_api/json_frm_parse.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o json_frm_parse.o ../json_api/json_frm_parse.cpp
	
dictionary.o: ../libs/iniparser-2.14/dictionary.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dictionary.o ../libs/iniparser-2.14/dictionary.cpp
	
iniparser.o: ../libs/iniparser-2.14/iniparser.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o iniparser.o ../libs/iniparser-2.14/iniparser.cpp
	
strlib.o: ../libs/iniparser-2.14/strlib.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o strlib.o ../libs/iniparser-2.14/strlib.cpp
	
iniSystem.o: ../common/iniSystem.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o iniSystem.o ../common/iniSystem.cpp

####### Install


