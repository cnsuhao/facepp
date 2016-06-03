/******************************************************************
@file name:   http_post.cpp

@brief: 

@note

@author sliang 358776565@qq.com

@version/date 2016-05-17
******************************************************************/
#define LOG_TAG				"face++.http.post"

#include <iostream>
#include <curl/curl.h>
#include "http_get.h"

namespace fpp 
{

size_t chunk::handle(char* data, size_t size, size_t nmemb, void* p)
{
    return static_cast<chunk*>(p)->m_handle_impl(data, size, nmemb);
}

size_t chunk::m_handle_impl(char* data, size_t size, size_t nmemb)
{
    m_content.append(data, size * nmemb);
    return size * nmemb;
}

std::string chunk::get_content() 
{
    return m_content;
}


int HttpClient::post(const std::string & strUrl, const std::map<std::string,std::string> & mapPost, std::string & strResponse)
{
	std::string strPost = "api_secret="+FACE_SECRET+"&api_key="+FACE_KEY;
	std::map<std::string,std::string>::const_iterator it = mapPost.begin();
	while (it != mapPost.end())
	{	
		strPost += "&";
		strPost += it->first;
		strPost += "=";
		strPost += it->second;
		it++;
	}
	return Post(strUrl,strPost,strResponse);
}

int HttpClient::post(const std::string & strUrl, const std::string & strPost, std::string & strResponse)
{
    CURL 		*curl;
    CURLcode 	res;
    HttpClient 	cself;

	CURLcode res;
	curl = curl_easy_init();
	if(!curl)
		return "";
	
	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_POST, 1);						// Regular HTTP POST
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());	// post content
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);				// Read the data is passed to the remote host, 3rd para: size_t function(void *ptr, size_t size, size_t nmemb,void *stream) 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);		
	curl_easy_setopt(curl, CURLOPT_FILE, (void *)&strResponse);		// #define CURLOPT_FILE CURLOPT_WRITEDATA /* name changed in 7.9.7 */
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);					// Ignore signals corresponding to the processing function
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);				// Waiting time before successfully connect to the server
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);						// From the server receives the buffer needs to wait for how long before completion
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
        std::cout << curl_easy_strerror(res) << std::endl;
        return "";
    }
	curl_easy_cleanup(curl);
	return res;
}


std::string get(std::string url) 
{
    CURL 		*curl;
    CURLcode 	res;
    HttpClient 	cself;
 
    //curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) 
        return "";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cself);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &chunk::handle);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cout << curl_easy_strerror(res) << std::endl;
        return "";
    }

    curl_easy_cleanup(curl);
    //curl_global_cleanup();

    return cself.get_content();
}

}


