/******************************************************************
@file name:   global.h

@brief:
     Global parameters defined

@note

@author sliang

@version/date 2016-04-12

******************************************************************/

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#define DB_OPERATE_REPEAT_100		100
#define DB_OPERATE_REPEAT_1000		1000
#define DB_OPERATE_REPEAT_10000		10000
#define DB_OPERATE_REPEAT_30000		30000
#define DB_OPERATE_REPEAT_100000	100000
#define DB_OPERATE_REPEAT			DB_OPERATE_REPEAT_30000

#define DB_OPERATE_USLEEP_100		100		// 100us
#define DB_OPERATE_USLEEP_1000		1000	// 1000us
#define DB_OPERATE_USLEEP			DB_OPERATE_USLEEP_100

#define DB_OPERATE_TIMEOUT       	10


#define ROBOT_DEF_SERVER_PORT_H         8090   	// HTTP => server
#define ROBOT_DEF_SERVER_PORT_R         10026   // robot => server
#define ROBOT_DEF_SERVER_PORT_M         10027   // phone => server
#define ROBOT_DEF_SERVER_PORT_W        	10028   // webServer => server


#define DATA_FILE_PATH			"/usr/runpara"


typedef enum webSer_login_ack{
	LOGIN_ACK_SUCCEND	=0,
	LOGIN_ACK_FAIL,
	LOGIN_ACK_INFOFAIL
}webSer_login_ack_t;

typedef struct sysPara{
	UINT32 clrLog_ndayAgo;
}sysPara_t;


typedef struct loginWebSerPara{
	char webserver_ip[32];
	UINT32 webserver_port;
	char webserver_name[64];
	char webserver_pwd[128];
}loginWebSerPara_t;


typedef struct serverPara{
	UINT32 robot_port;
	UINT32 mobile_port;
	UINT32 webclient_port;
}serverPara_t;



#ifdef __cplusplus
}
#endif

#endif

