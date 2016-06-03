/******************************************************************
@file name:   httputil.c

@brief: Completing the HTTP post and get request, as well as the data download

@note

@author sliang 358776565@qq.com

@version/date 2016-04-15
******************************************************************/
#define LOG_TAG			"robots.httputil"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#include "ghttp.h"
#include "retcode.h"
#include "global.h"
#include "json_packet.h"
#include "debug.h"
#include "httputil.hpp"

usring namespace std;

loginWebSerPara_t gToWebKey;


#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}

int isFileExist(char * savePath) 
{
    if (!access(savePath, F_OK)) {
        return 1;
    } else {
        return 0;
    }
}


int download(char *uri, char *savePath) 
{
    ghttp_request *request = NULL;
    ghttp_status status;
    FILE * pFile;
    char *buf;
    int bytes_read;
    int size = -1;
    int err = -1;
    
    if(!isFileExist(savePath))
    {
        LOGE("savePath not exist.");
        err = ERRCODE_HTTP;
        goto retEnd;
    }
    pFile = fopen(savePath, "wb");
    request = ghttp_request_new();
    if(pFile==NULL || request==NULL){
        err = ERRCODE_HTTP;
        goto end;
    }
    if (ghttp_set_uri(request, uri) == -1)
        return -1;
    if (ghttp_set_type(request, ghttp_type_get) == -1)
        return -1;
    ghttp_prepare(request);
    status = ghttp_process(request);
    if (status == ghttp_error)
        return -1;

    buf = ghttp_get_body(request);
    bytes_read = ghttp_get_body_len(request);
    size = strlen(buf); //size == bytes_read
    fwrite(buf, 1, size, pFile);

 end:
	if(pFile)    {fclose(pFile);}
	if(request){
		ghttp_close(request);
		ghttp_clean(request);
	} 
retEnd:
    return err;   
}


int netGet(char* url, char* params, int timeout, char *result, int *result_len) 
{
	int err = ERRCODE_SUCCESS;
    ghttp_request *request = NULL;
    
    request = ghttp_request_new();
    if(request == NULL){
    	err = ERRCODE_HTTP;
    	goto retEnd;
    }
  
    if(params!=NULL&&strlen(params)>0)
    {
        char tmp[1024];
        strncpy(tmp, url, strlen(url));
        if(strchr(tmp, '?') == NULL)	//url nonexistence
        {     
        	strncat(tmp,"?", 1)  ;          
        }
        strncat(tmp,params, strlen(params)) ;  
        LOGD("%s\n",tmp);
        ghttp_set_uri(request, tmp);      
    }
    else{
         ghttp_set_uri(request, url);
    } 
    ghttp_set_type(request, ghttp_type_get); //get method
    ghttp_set_header(request, http_hdr_Connection, "close");
    char timeout_str[10];
    snprintf(timeout_str, sizeof(timeout_str)-strlen(timeout), "%d", timeout);
    ghttp_set_header(request, http_hdr_Timeout, timeout_str);  
   
    ghttp_prepare(request);
    ghttp_process(request);
    
    *result_len = ghttp_get_body_len(request);

	if((*result_len <= 0) || (*result_len >= JSON_RET_FRM_LENGTH)){
		LOGE("get: josn return NULL or too long\n");
		err = ERRCODE_HTTP_OVERFLOW;
		goto end;
	}
	strncpy(result, ghttp_get_body(request), *result_len);
    
end:
	if(request)
		ghttp_request_destroy(request);
retEnd:
    return err;
}


int Post(const string & strUrl, const map<string,string> & mapPost, string & result_json, int & result_len, int timeout)
{
	string strPost = "api_secret="+FACE_SECRET+"&api_key="+FACE_KEY;
	map<string,string>::const_iterator it = mapPost.begin();
	while (it != mapPost.end())
	{	
		strPost += "&";
		strPost += it->first;
		strPost += "=";
		strPost += it->second;
		it++;
	}
	return Post(strUrl,strPost,result_json, result_len, timeout);
}

int netPost(const string & strUrl, const string & strPost, string &result, int &result_len, int timeout) 
{
	int err = ERRCODE_SUCCESS;
    ghttp_request *request = NULL;
    ghttp_status status;
    int len=-1, retLen=-1;

    LOGD("http request = %s%s\n", strUrl,strPost); 
	
    request = ghttp_request_new();
    if(request == NULL){
		LOGE("http request: Failure to apply for space\n");	
		err = ERRCODE_HTTP;
		goto retEnd;
    }
    if (ghttp_set_uri(request, strUrl) == -1){
		err = ERRCODE_HTTP;
		goto end;
	}
    if (ghttp_set_type(request, ghttp_type_post) == -1){ //post
		err = ERRCODE_HTTP;
		goto end;
	}
    ghttp_set_header(request, http_hdr_Content_Type, "application/x-www-form-urlencoded");
    
    char timeout_str[16];
    memset(timeout_str, 0, 16);
    cmn_itoa(timeout, timeout_str, 10);
    ghttp_set_header(request, http_hdr_Timeout, timeout_str);
    //ghttp_set_sync(request, ghttp_sync); //set sync
    len = strlen(strPost);
    ghttp_set_body(request, strPost, len); //
    ghttp_prepare(request);
    status = ghttp_process(request);
    if (status == ghttp_error){
    	LOGE("http request process fail\n");
		err = ERRCODE_HTTP;
		goto end;
	}
    *result_len=ghttp_get_body_len(request);
	if((*result_len <= 0) || (*result_len >= JSON_RET_FRM_LENGTH)){						
		LOGE("josn return NULL or too long, length=%d\n", *result_len);
		err = ERRCODE_HTTP_OVERFLOW;
		goto end;
	}
    strncpy(result, ghttp_get_body(request), *result_len);
	
end:
	if(request){
		ghttp_close(request);
		ghttp_clean(request);
	}
retEnd:
    return err;
}

#if 0
	status = ghttp_process(request);  
        if(status == ghttp_error)  
            break;  
        /* NOTE: buf may NULL, notice it */  
        buf = ghttp_get_body(request);  
        bytes_read = ghttp_get_body_len(request);  
        if(status == ghttp_done) {  
            /* NOTE: Ok, done */  
            break;  
        }   
#endif