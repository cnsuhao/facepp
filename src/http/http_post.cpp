/******************************************************************
@file name:   http_post.cpp

@brief:
     Defines the entry point for the console application
 
Instructions:
	HttpClient httpClient;
	httpClient.Post(HttpClient::URL_DETECT,"url=http://g.hiphotos.baidu.com/image/pic/item/0df431adcbef7609758498962cdda3cc7cd99e2f.jpg&api_secret=own secret&api_key=own key",strResult);
	std::map<std::string,std::string> mapPost;
	mapPost["url"] = "http://g.hiphotos.baidu.com/image/pic/item/0df431adcbef7609758498962cdda3cc7cd99e2f.jpg";
	mapPost["img"] = "c:\\test.jpg";
	httpClient.Post(HttpClient::URL_DETECT,mapPost,strResult);	
	std::cout<<std::endl<<strResult<<std::endl;

@note

@author sliang 358776565@qq.com

@version/date 2016-05-13
******************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include "http_post.h"
#include "curl/curl.h"

#define LOG_TAG	zlog_get_category("http.post")


using namespace std;

namespace fpp 
{

size_t http_post::callback(void* data, size_t size, size_t nmemb, void* stream)
{
	return static_cast<http_post*>(stream)->m_handle_impl(data, size, nmemb);
}

size_t http_post::m_handle_impl(char* data, size_t size, size_t nmemb)
{
    m_content.append(data, size * nmemb);
    return size * nmemb;
}

std::string http_post::get_content() 
{
    return m_content;
}


size_t WriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
	std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
	if( NULL == str || NULL == buffer )
	{
		LOGD("accept data is NULL.\n");
		return -1;
	}
    char* pData = (char*)buffer;
	LOGD("accept data is: \n%s\n", pData);
    str->append(pData, size * nmemb);
	return nmemb;
} 


int post_file(const std::string & strUrl, std::map<std::string,std::string> mapPost, std::string file)
{
	int result;
	CURLcode res;
	struct curl_httppost *formpost=NULL;
	struct curl_httppost *lastptr=NULL;
	//LOGD(category, "url = %s, file = %s\n",strUrl.c_str(), file.c_str());
	
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key", 
		CURLFORM_COPYCONTENTS, "you key", 
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret", 
		CURLFORM_COPYCONTENTS, "you secret",
		CURLFORM_END);
/*	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "group_name", 
		CURLFORM_COPYCONTENTS, "Family",
		CURLFORM_END);
*/
#if 1	
    //上传文件，指定本地文件完整路径
    if(curl_formadd(&formpost, 
    	&lastptr, 
    	CURLFORM_COPYNAME, 		"img", 
    	CURLFORM_FILE, 			"/home/project/libface++/bin/7.jpg", 
    	CURLFORM_CONTENTTYPE,  	"image/jpeg", 	//"application/x-jpg",			
    	CURLFORM_END) != 0){
		//LOGE(category, "post file fail.");
		result = -1;
		goto func_end;
	}
	curl_formadd(&formpost, &lastptr,
			 CURLFORM_COPYNAME, "submit",
			 CURLFORM_COPYCONTENTS, "OK",
			 CURLFORM_END);

#else
	char* file_data = NULL;
	long file_size = 0;
	long read_size = 0;
	
	FILE* fp = fopen(file.c_str(), "rb");
	if (fp)
	{		
		fseek(fp, 0, SEEK_END);
		file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		file_data = new char[file_size+1];
		read_size = fread(file_data,1,file_size,fp);
		LOGE(category,"read file: file_size=%ld, read_size=%ld", file_size, read_size);
		fclose(fp);
	}
	
	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "img",				// Upload the field key name
		CURLFORM_BUFFER, "test.jpg",			// Specify name of the file in service side; It is used to tell libcurl file content already in the cache
		CURLFORM_BUFFERPTR, file_data,			// file data
		CURLFORM_BUFFERLENGTH, file_size,		// Specify the file size
		CURLFORM_CONTENTTYPE, "image/jpeg",		// Specify the upload file type is jpeg or jpg
		CURLFORM_END);
#endif
	CURL* curl = curl_easy_init();
	if(NULL == curl)
	{
		LOGE("zlog initialize fail.");
		result = -1;
		goto func_end;
	}
	string HTTPRESULT;
	/* what URL that receives this POST */ 
	// Set related parameters of the request to make curl agreement or returns the specified data
	curl_easy_setopt(curl, CURLOPT_URL, strUrl);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);				// to upload a file with URL
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &HTTPRESULT);			// The object pointer data storage, such as string HTTPRESULT;Can also be a file stream fp
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &http_post::callback);		// Set the callback function when the result data arrived
	//curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);			// Waiting time before successfully connect to the server
	//curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

	char error[1024];
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error);				// set error buffer for error messages

	res = curl_easy_perform(curl);									// 执行curl的各种操作
	if(res != CURLE_OK){
		LOGE("error:%s\n", curl_easy_strerror(res));
		result = -1;
		goto func_end;
	} 
	result = 0;

func_end:
	if(curl) 		curl_easy_cleanup(curl);
	if(formpost)	curl_formfree(formpost);
	//if(file_data)	delete [] file_data;
	return result;
}


std::string post(const std::string &strUrl, const std::string &postPara)
{
	CURLcode res;
	http_post post;
	CURL* curl = NULL;
	LOGD("post url is:%s?%s", strUrl.c_str(), postPara.c_str());
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if(NULL == curl)
	{
		LOGE("initialize libcurl fail.");
		return "";
	}
	
	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_POST, 1);						// Regular HTTP POST
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postPara.c_str());	// post content
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);				// Read the data is passed to the remote host, 3rd para: size_t function(void *ptr, size_t size, size_t nmemb,void *stream) 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &post);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &http_post::callback);	// callback function	
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);					// Ignore signals corresponding to the processing function
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5);				// Waiting time before successfully connect to the server
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 7);						// From the server receives the buffer needs to wait for how long before completion


	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		LOGE("error:%s\n", curl_easy_strerror(res));
        return "";
    }
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	
	return post.get_content();
}


int posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath)
{
	CURLcode res;
	CURL* curl = curl_easy_init();
	if(NULL == curl)
	{
		return CURLE_FAILED_INIT;
	}
	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &http_post::callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	if(NULL == pCaPath)
	{
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
	}
	else
	{
		//Default is PEM, so don't need to set up, the other support DER
		//curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);
	}
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return res;
}
}

