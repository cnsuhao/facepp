#ifndef JSON_ACCESS_API_H
#define JSON_ACCESS_API_H

#include "types.h"
#include "retcode.h"
#include <json/json.h>


#ifdef __cplusplus
extern "C" {
#endif

#define FRM_HDR_TAG_STR_LEN 20



typedef struct jfrm_bdy {	
	INT32 ret;

} jfrm_bdy_t;


typedef struct jfrm_hdr{	
	INT32 ret;

} jfrm_hdr_t;


/******************************************************************
@name json_api_judge_keyName_isExist()

@brief  judge name of key is exit or not
	

@params
	val ---> reference to object value

	key_name ---> buffer for accomdating string of name of key,


@return 
	return TRUE if everything is okay, else FALSE

@note  

=================================================*/
BOOL json_api_judge_keyName_isExist(Json::Value& val, char* key_name); 


/******************************************************************
@name json_api_fetch_key_str_val()

@brief  fetch value with string format according to name of key
	

@params
	val ---> reference to object value

	key_name ---> buffer for accomdating string of name of key,
	key_val ---> buffer for putting  result ,


@return 
	return error code, pls refer to above definition

@note  Make sure that key_val buffer is valid and
		length of it is suffcient

=================================================*/
INT32 json_api_fetch_key_str_val(Json::Value& val, char* key_name, char* key_val);



/******************************************************************
@name json_api_fetch_key_int_val()

@brief  fetch value with integer format according to name of key
	

@params
	val ---> reference to object value

	key_name ---> buffer for accomdating string of name of key,
	key_val ---> buffer for putting  result ,


@return 
	return error code, pls refer to above definition

@note  Make sure that key_val buffer is valid and

=================================================*/
INT32 json_api_fetch_key_int_val(Json::Value& val, IN char* key_name, OUT INT32* key_val);
void json_api_fast_fetch_c_str(IN Json::Value& val,  IN char* key_name, OUT char* str);
void json_api_convert_val_to_c_str(IN Json::Value& val,  OUT char* str);
void json_api_fast_fetch_integer(IN Json::Value& val,  IN char* key_name, OUT int* key_val);
void json_api_print_data(IN Json::Value& val, const char* tipInfo=NULL);

INT32 parse_frame_hdr(Json::Value json_val, OUT jfrm_hdr_t* headr);
INT32 parse_frame_body(Json::Value json_val, OUT jfrm_bdy_t* body);



#ifdef __cplusplus
}
#endif


#endif // JSON_ACCESS_API_H




