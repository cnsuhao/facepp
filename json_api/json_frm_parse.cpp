/******************************************************************
@file name:   json_frm_parse.c

@brief: Parsing the json data frame

@note

@author sliang 358776565@qq.com

@version/date 2016-04-20
******************************************************************/
#define LOG_TAG				"robots.json.frm.parse"

#include <string.h>
#include "debug.h"
#include "json_frm_parse.h"
#include "json_access_api.h"
#include "json_packet.h"


int login_json_to_str_parse(const char *jsonFrm,  const char *buf)
{
	int ret = -1;
	Json::Reader reader;
	Json::Value root;
	jfrm_bdy_t frm_bdy;

	memset(&frm_bdy, 0, sizeof(frm_bdy));

	if(jsonFrm && buf)
	{
		ret = ERRCODE_CCT;
		goto end;
	}
	if(!reader.parse(std::string(jsonFrm), root, false)){
		LOGE("-call lib err or json fmt invalid\n--->%s\n", jsonFrm);
		ret = ERRCODE_JSON_FORMAT_ERR;
		goto end;
	}
	parse_frame_body(root, &frm_bdy);

end:
	return ret;
}


int recv_json_to_str_parse(const char *jsonFrm,  const char *buf)
{
	int ret = -1;

end:
	return ret;
}

/******************************************************************
@brief:  fetch value Success or not according to name of key;
		 Applied to the HTTP request to return the result judgement
@params:
	json_result ---> reference to object value
	dataKey ---> buffer for accomdating string of name of key,

@return: 
	return error code, pls refer to retcode.h definition

@note:  Make sure that dataKey buffer is valid
=================================================================*/
int request_result_parse(const char *json_result, char *dataKey)
{
	int err = ERRCODE_CCT;
	Json::Reader reader;
	Json::Value root;
	Json::Value data;
	char isPass[16];

	if(!reader.parse(std::string(json_result), root, false)){
		LOGE("-call lib err or json fmt invalid\n--->%s\n", json_result);
		err = ERRCODE_JSON_FORMAT_ERR;
		goto goto_enddata;
	}
	json_api_print_data(root, LOG_TAG);

	if(!json_api_judge_keyName_isExist(root, FRM_ACK_BASE_CODE)){
		err = ERRCODE_JSON_PARAM_ERR;
		LOGE("-call lib err or json keyName(%s) invalid\n", FRM_ACK_BASE_CODE);
		goto goto_enddata;
	}
	// if key code not equal to "200" eixt;
	if(strcmp(root[FRM_ACK_BASE_CODE].asString().c_str(), "200")){
		err = ERRCODE_JSON_PARAM_ERR;
		LOGE("-get key value err; keyName(%s)\n", FRM_ACK_BASE_CODE);
		goto goto_enddata;
	}
		
	if(!json_api_judge_keyName_isExist(root, FRM_ACK_BASE_DATA)){
		err = ERRCODE_JSON_PARAM_ERR;
		LOGE("-call lib err or json keyName(%s) invalid\n", FRM_ACK_BASE_DATA);
		goto goto_enddata;
	}
	
	data = root[FRM_ACK_BASE_DATA];
	if (!json_api_judge_keyName_isExist(data, dataKey)) {
		err = ERRCODE_JSON_PARAM_ERR;
		LOGE("-call lib err or json keyName(%s) invalid\n", dataKey);
		goto goto_enddata;		
	}
	if(strlen(data[dataKey].asString().c_str()) >= 16){
		err = ERRCODE_JSON_PARAM_ERR;
		LOGE("-keyName(%s) value invalid, too loog\n", dataKey);
		goto goto_enddata;	
	}
	strncpy(isPass, data[dataKey].asString().c_str(), strlen(data[dataKey].asString().c_str()));	
	
	if(!strcmp(isPass, RESULT_YES)){
		err = ERRCODE_SUCCESS;
	}

goto_enddata:
	return err;
}