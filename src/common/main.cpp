/******************************************************************
@file name:   main.cpp

@brief:
     main function

@note

@author sliang 358776565@qq.com

@version/date 2016-05-13
******************************************************************/
#include <string>
#include <iostream>
#include "HttpClient.h"
#include "curl/curl.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "recognition.h"
#include "zlog.h"


using namespace std;
using namespace rapidjson;

#define LOG_TAG	zlog_get_category("face.main")


int main(int argc, char* argv[])
{
	int rc;
	zlog_category_t *zg;
	rc = zlog_init("zlog_config.conf");	
	if (rc) {		
		printf("init zlog failed\n");		
		return -1;	
	}
	LOGD("init zlog succeed!");

#if 0
	CURL *curl = curl_easy_init();
	/*curl_global_init(long flags)   flags: 
	* CURL_GLOBAL_ALL     //初始化所有的可能的调用。
	* CURL_GLOBAL_SSL     //初始化支持 安全套接字层。
	* CURL_GLOBAL_WIN32   //初始化win32套接字库。
	* CURL_GLOBAL_NOTHING //没有额外的初始化。 */
	CURLcode res = curl_global_init(CURL_GLOBAL_WIN32);

	std::string strJson;
	rapidjson::Document result;
	HttpClient HttpClient;
	
	std::map<std::string, std::string> mapPost;
	//mapPost["url"] = "http://www.faceplusplus.com/static/img/demo/7.jpg";
	mapPost["img"] = "/home/project/libface++/bin/7.jpg"; 
	mapPost["group_name"] = "Family";
	HttpClient.Post(HttpClient::URL_RECOGNIZE, mapPost, strJson);
	//HttpClient.Post_file(HttpClient::URL_DETECT, mapPost, "/home/project/libface++/bin/7.jpg");
	result.Parse<rapidjson::kParseStopWhenDoneFlag>(strJson.c_str());
#endif


	try{        
		fpp::recognition recognition("apikey.cfg");        
		std::vector<fpp::candidate_t> candidates = recognition.identify(                
			"http://www.faceplusplus.com/static/img/demo/13.jpg",                 
			"Family"
			);        
		fpp::candidate_t candidate = recognition.get_confident_candidate(candidates);        
		std::cout << candidate.person_name << std::endl;    
	}     
	catch (std::string ex) {        
		std::cout << ex << std::endl;   
	}

	return 0;
}
