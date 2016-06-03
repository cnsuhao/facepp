/******************************************************************
@file name:   FacePlusPlus.cpp

@brief:
     Defines the entry point for the console application

@note

@author sliang 358776565@qq.com

@version/date 2016-045-13
******************************************************************/
#include <string>
#include <iostream>
#include "HttpClient.h"
#include "curl/curl.h"
#include "curl/easy.h"

using namespace std;
std::string strResult;
std::string HTTPRESULT;

void Write_data(void* buffer, size_t size, size_t nmemb, void* user_p){
	HTTPRESULT += (const char*)buffer;
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	HttpClient httpClient;
	httpClient.Post(HttpClient::URL_DETECT,"url=http://g.hiphotos.baidu.com/image/pic/item/0df431adcbef7609758498962cdda3cc7cd99e2f.jpg&api_secret=own secret&api_key=own key",strResult);
	std::map<std::string,std::string> mapPost;
	mapPost["url"] = "http://g.hiphotos.baidu.com/image/pic/item/0df431adcbef7609758498962cdda3cc7cd99e2f.jpg";
	mapPost["img"] = "c:\\test.jpg";
	httpClient.Post(HttpClient::URL_DETECT,mapPost,strResult);	
	std::cout<<std::endl<<strResult<<std::endl;
	*/

	CURL *curl = curl_easy_init();
	/*curl_global_init(long flags)   flags: 
	* CURL_GLOBAL_ALL     //初始化所有的可能的调用。
	* CURL_GLOBAL_SSL     //初始化支持 安全套接字层。
	* CURL_GLOBAL_WIN32   //初始化win32套接字库。
	* CURL_GLOBAL_NOTHING //没有额外的初始化。 */
	CURLcode res = curl_global_init(CURL_GLOBAL_WIN32);

	struct curl_httppost *formpost=NULL;
	struct curl_httppost *lastptr=NULL;
	//        struct curl_slist *headerlist=NULL;
	//        static const char buf[] = "Expect:";

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key", 
		CURLFORM_COPYCONTENTS, "private key", 
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret", 
		CURLFORM_COPYCONTENTS, "own secret",
		CURLFORM_END);
	/*
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "img", 
		CURLFORM_FILE, "c:\\test.png", 
		CURLFORM_END);
		*/
	
	char* file_data = NULL;
	long file_size = 0;
	
	FILE* fp = fopen("c:\\test.jpg","rb");
	if (fp)
	{		
		fseek(fp, 0, SEEK_END);
		file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		file_data = new char[file_size+1];
		fread(file_data,1,file_size,fp);
		cout<<file_data<<endl;
		fclose(fp);
	}
	
	
	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "img",
		CURLFORM_BUFFER, "test.jpg",
		CURLFORM_BUFFERPTR, file_data,
		CURLFORM_BUFFERLENGTH, file_size,
		CURLFORM_CONTENTTYPE, "image/jpeg",
		CURLFORM_END);
		
	
	if(curl) {
		/* what URL that receives this POST */ 
		// Set related parameters of the request to make curl agreement or returns the specified data
		curl_easy_setopt(curl, CURLOPT_URL, "http://apicn.faceplusplus.com/v2/detection/detect");
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &HTTPRESULT);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Write_data);

		char error[1024];
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error);

		res = curl_easy_perform(curl);
		if(res != CURLE_OK) cout<<endl<<error<<endl;
	}
	curl_easy_cleanup(curl);
	curl_formfree(formpost);
	cout<<endl<<HTTPRESULT<<endl;

	if(file_data != NULL)
		delete [] file_data;
	system("pause");
	return 0;
}
