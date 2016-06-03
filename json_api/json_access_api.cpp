/******************************************************************
@file name:   json_access_api.c

@brief: Jsoncpp based interface encapsulation

@note

@author sliang 358776565@qq.com

@version/date 2016-04-12
******************************************************************/
#define LOG_TAG				"robots.json.access.api"

#include <string.h>
#include "json_access_api.h"
#include "debug.h"
#include "json_packet.h"

// inline 
inline bool __judge_keyName_isExit(Json::Value& val, char* key_name)
{
	return val.isMember(key_name);
}

// Return true if the object has a member named key.
BOOL json_api_judge_keyName_isExist(Json::Value& val, char* key_name)
{
	return (BOOL)__judge_keyName_isExit(val, key_name);
}



INT32 json_api_fetch_key_str_val(Json::Value& val, IN char* key_name, OUT char* key_val)
{
	if (__judge_keyName_isExit(val, key_name)) {
		std::string str = val[key_name].asString();
		
		strncpy(key_val, str.c_str(), strlen(str.c_str()));
		return ERRCODE_SUCCESS;
	}

	return ERRCODE_JSON_KEYNAME_NOEXIT;
}


INT32 json_api_fetch_key_int_val(Json::Value& val, IN char* key_name, OUT INT32* key_val)
{
	if (__judge_keyName_isExit(val, key_name)) {

		*key_val = val[key_name].asInt();
		return ERRCODE_SUCCESS;
	}

	return ERRCODE_JSON_KEYNAME_NOEXIT;
}

void json_api_fast_fetch_c_str(IN Json::Value& val,  IN char* key_name, OUT char* str)
{
	strncpy(str, val[key_name].asString().c_str(), strlen(val[key_name].asString().c_str()));
}

void json_api_convert_val_to_c_str(IN Json::Value& val,  OUT char* str)
{
	strncpy(str, val.toStyledString().c_str(), strlen(val.toStyledString().c_str()));
}


 void json_api_fast_fetch_integer(IN Json::Value& val, IN char* key_name, OUT int* key_val)
{
	*key_val = val[key_name].asInt();
}

void json_api_print_data(IN Json::Value& val, const char* tipInfo)
{
	char str[JSON_RET_FRM_LENGTH];
	
	strncpy(str, val.toStyledString().c_str(), JSON_RET_FRM_LENGTH);
	if(tipInfo){
		LOGD("%s: \n %s \n\n", tipInfo, str);
	}
	else{
		LOGD("json data: \n %s \n\n", str);
	}
}


INT32 parse_frame_hdr(IN Json::Value json_val, OUT jfrm_bdy* headr)
{
	
}

INT32 parse_frame_body(IN Json::Value json_val, OUT jfrm_bdy* body)
{
	
}

