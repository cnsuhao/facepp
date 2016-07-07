#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <map>
#include "zlog.h"


namespace fpp 
{

class http_post
{

public:
	static size_t callback(void* data, size_t size, size_t nmemb, void* stream);
	std::string get_content() ;

private:
	size_t m_handle_impl(char* data, size_t size, size_t nmemb);
	

private:
	zlog_category_t *category;
	std::string m_content;

};


/**
* @brief HTTP POST Request
* @param 
* @ 	strUrl: 	The input parameters, the requested Url address, such as: http://www.baidu.com
* @return:	Returns the POST whether successful
*/
std::string post(const std::string &strUrl, const std::string &postPara);

int post_file(const std::string & strUrl, std::map<std::string,std::string> mapPost, std::string file);

/**
* @brief HTTPS POST Request No certificate version
* @param 
* @ 	strUrl: 	The input parameters, the requested Url address, such as: http://www.baidu.com
* @ 	strPost:	The input parameters,key value format
* @ 	strResponse:The output parameters, result content
* @ 	pCaPath:	The input parameters for the path of the CA certificate. If the input is NULL, not to verify the validity of the certificate on the server.
* @return Returns the POST whether successful
*/
int posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath = NULL);
size_t WriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid);

}
#endif
