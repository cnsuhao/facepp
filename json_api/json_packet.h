/******************************************************************
@file name:   maintain.c

@brief: json frm define
     
@note 

@author  358776565@qq.com

@version/date 2016-04-18

******************************************************************/

#ifndef JSON_PACKET_H
#define JSON_PACKET_H

#ifdef __cplusplus
extern "C" {
#endif

#define RESULT_YES				"true"
#define RESULT_NO				"false"


#define FRM_ACK_BASE_CODE		"code"
#define FRM_ACK_BASE_DATA		"data"
#define FRM_ACK_BASE_MESSAGE	"message"

#define FRM_ACK_DATA_ISPASS		"isPass"
#define FRM_ACK_DATA_ISMODIFY	"isModify"
#define FRM_ACK_DATA_ISBIND		"isBind"


#define REQ_KEY_ROBOT_ID		"robotId"
#define REQ_KEY_USER_ID			"userId"
#define REQ_KEY_PASSWORD		"password"
#define REQ_KEY_STATUS			"status"
#define REQ_KEY_SOCKET_NAME		"serverName"
#define REQ_KEY_SOCKET_PWD		"serverPassword"



#define JSON_RET_FRM_LENGTH		8096

typedef struct json_frm{
	
}json_frm_t;

#ifdef __cplusplus
}
#endif
#endif
