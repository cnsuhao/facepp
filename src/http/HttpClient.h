#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <map>
#include "zlog.h"

/*
CURLOPT_HEADER��					//��Ϊ1�����ڷ��ص����������http header��
CURLOPT_FOLLOWLOCATION��			//��Ϊ0���򲻻��Զ�301��302��ת��
*CURLOPT_INFILESIZE: 				//�����ϴ�һ���ļ���Զ��վ�㣬���ѡ�����PHP���ϴ��ļ��Ĵ�С��
*CURLOPT_VERBOSE: 					//�������CURL����ÿһ����������飬�������ѡ��Ϊһ������ֵ��
*CURLOPT_HEADER: 					//��������һ��ͷ����������У��������ѡ��Ϊһ������ֵ��
*CURLOPT_NOPROGRESS: 				//����㲻��PHPΪCURL������ʾһ�����������������ѡ��Ϊһ������ֵ��

 

//ע�⣺PHP�Զ��������ѡ��Ϊ����ֵ����Ӧ�ý���Ϊ�˵��Ե�Ŀ�����ı����ѡ�

*CURLOPT_NOBODY: 					//����㲻��������а���body���֣��������ѡ��Ϊһ������ֵ��
*CURLOPT_FAILONERROR: 				//���������PHP�ڷ�������(HTTP���뷵�ش��ڵ���300)ʱ������ʾ���������ѡ��Ϊһ�˷���ֵ��Ĭ����Ϊ�Ƿ���һ������ҳ�����Դ��롣
*CURLOPT_UPLOAD: 					//���������PHPΪ�ϴ���׼�����������ѡ��Ϊһ������ֵ��
*CURLOPT_POST: 						//�������PHPȥ��һ�������HTTP POST���������ѡ��Ϊһ������ֵ�����POST����ͨ�� application/x-www-from-urlencoded ���ͣ�������HTML��ʹ�á�
*CURLOPT_FTPLISTONLY: 				//�������ѡ��Ϊ����ֵ��PHP���г�FTP��Ŀ¼���б�
*CURLOPT_FTPAPPEND: 				//�������ѡ��Ϊһ������ֵ��PHP��Ӧ��Զ���ļ����渲������
*CURLOPT_NETRC: 					//�������ѡ��Ϊһ������ֵ��PHP������� ~./netrc �ļ��в�����Ҫ�������ӵ�Զ��վ����û��������롣
*CURLOPT_FOLLOWLOCATION: 			//�������ѡ��Ϊһ������ֵ(�� ��Location: ��)��ͷ�����������������HTTPͷ��һ���ַ���(ע�����ǵݹ�ģ�PHP���������� ��Location: ����ͷ)��
*CURLOPT_PUT: 						//�������ѡ��Ϊһ������ֵȥ��HTTP�ϴ�һ���ļ���Ҫ�ϴ�����ļ���������CURLOPT_INFILE��CURLOPT_INFILESIZEѡ��.
*CURLOPT_MUTE: 						//�������ѡ��Ϊһ������ֵ��PHP����CURL��������ȫ��Ĭ��
*CURLOPT_TIMEOUT: 					//����һ��������������Ϊ������������롣
*CURLOPT_LOW_SPEED_LIMIT: 			//����һ���������������ƴ��Ͷ����ֽڡ�
*CURLOPT_LOW_SPEED_TIME: 			//����һ���������������ƶ����봫��CURLOPT_LOW_SPEED_LIMIT�涨���ֽ�����
*CURLOPT_RESUME_FROM: 				//����һ�������ֽ�ƫ�Ƶ�ַ�ĳ����β�����(����ת�Ƶ��Ŀ�ʼ��)��
*CURLOPT_SSLVERSION: 				//����һ������SSL�汾�ĳ�������Ĭ��PHP�������Լ�Ŭ����ȷ�����ڸ���İ�ȫ��������ֹ����á�
*CURLOPT_TIMECONDITION: 			//����һ����������ָ����ô����CURLOPT_TIMEVALUE����������������������ΪTIMECOND_IFMODSINCE �� TIMECOND_ISUNMODSINCE���������HTTP��
*CURLOPT_TIMEVALUE: 				//����һ����1970-1-1��ʼ�����ڵ����������ʱ�佫��CURLOPT_TIMEVALUEѡ����Ϊָ��ֵʹ�ã���Ĭ��TIMECOND_IFMODSINCEʹ�á�

//����ѡ���ֵ������Ϊ�ַ�����

*CURLOPT_URL: 				//����������PHPȡ�ص�URL��ַ����Ҳ��������curl_init()������ʼ��ʱ�������ѡ�
*CURLOPT_USERPWD: 			//����һ������[username]:[password]�����ַ���,����PHPȥ���ӡ�
*CURLOPT_PROXYUSERPWD:	 	//����һ������[username]:[password] ��ʽ���ַ���ȥ����HTTP����
*CURLOPT_RANGE: 			//����һ������ָ���ķ�Χ����Ӧ���ǡ�X-Y����ʽ��X��Y�Ǳ�����ġ�HTTP����ͬ��֧�ּ���������ö������ָ�(X-Y,N-M)��
*CURLOPT_POSTFIELDS: 		//����һ����ΪHTTP ��POST���������������ݵ��ַ�����
*CURLOPT_REFERER: 			//��HTTP�����а���һ����referer��ͷ���ַ�����
*CURLOPT_USERAGENT: 		//��HTTP�����а���һ����user-agent��ͷ���ַ�����
*CURLOPT_FTPPORT: 			//����һ��������ftp ��POST��ָ��ʹ�õ�IP��ַ�����POSTָ�����Զ�̷�����ȥ��������ָ����IP��ַ������ַ���������һ��IP��ַ��һ����������һ�����������(��UNIX��)�����ǡ�-��(ʹ��ϵͳĬ��IP��ַ)��
*CURLOPT_COOKIE: 			//����һ������HTTP cookie��ͷ���ӡ�
*CURLOPT_SSLCERT: 			//����һ������PEM��ʽ֤����ַ�����
*CURLOPT_SSLCERTPASSWD: 	//����һ������ʹ��CURLOPT_SSLCERT֤���������롣
*CURLOPT_COOKIEFILE: 		//����һ������cookie���ݵ��ļ������ֵ��ַ��������cookie�ļ�������Netscape��ʽ�����ǶѴ����ļ��е�HTTP����ͷ��
*CURLOPT_CUSTOMREQUEST: 	//������HTTP����ʱ������һ���ַ���GET��HEADʹ�á�Ϊ����DELETE����������������ģ���Pass a string to be used instead of GET or HEAD when doing an HTTP request. This is useful for doing or another, more obscure, HTTP request.

//ע��: ��ȷ����ķ�����֧�������Ȳ�Ҫȥ��������

//���е�ѡ��Ҫ��һ���ļ�����(ͨ��ʹ��fopen()�������)��
*CURLOPT_FILE: 			//����ļ���������ô��͵�����ļ���Ĭ����STDOUT.
*CURLOPT_INFILE: 		//����ļ����㴫�͹����������ļ���
*CURLOPT_WRITEHEADER: 	//����ļ�д���������ͷ���֡�
*CURLOPT_STDERR: 		//����ļ�д�д��������stderr��
*/

class HttpClient
{
public:
	HttpClient(void);
	~HttpClient(void);

public:

	std::string ftp_upload(std::string filename, 
                       std::string username, 
                       std::string password, 
                       std::string ftp_url = "ftp://v0.ftp.upyun.com/tmp/");
	/**
	* @brief HTTP POST Request
	* @param 
	* @		strUrl: 	The input parameters, the requested Url address, such as: http://www.baidu.com
	* @		mapPost:	The input parameters,key value format
	* @ 	strResponse:The output parameters, result content
	* @return: 	Returns the POST whether successful
	*/
	int Post(const std::string & strUrl, const std::map<std::string,std::string> & mapPost, std::string & strResponse);

	/**
	* @brief HTTP POST Request
	* @param 
	* @		strUrl:		The input parameters, the requested Url address, such as: http://www.baidu.com
	* @ 	strPost:	The input parameters,key value format
	* @ 	strResponse:The output parameters, result content
	* @return:	Returns the POST whether successful
	*/
	int Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse);

	int Post_file(const std::string & strUrl, std::map<std::string,std::string> mapPost, std::string file);

	/**
	* @brief HTTP GET Request
	* @param 
	* @		strUrl: 	The input parameters, the requested Url address, such as: http://www.baidu.com
	* @ 	strResponse:The output parameters, result content
	* @return: 	Returns the POST whether successful
	*/
	int Get(const std::string & strUrl, std::string & strResponse);

	/**
	* @brief HTTPS POST Request No certificate version
	* @param 
	* @		strUrl: 	The input parameters, the requested Url address, such as: http://www.baidu.com
	* @ 	strPost: 	The input parameters,key value format
	* @ 	strResponse:The output parameters, result content
	* @ 	pCaPath: 	The input parameters for the path of the CA certificate. If the input is NULL, not to verify the validity of the certificate on the server.
	* @return Returns the POST whether successful
	*/
	int Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath = NULL);

	/**
	* @brief HTTPS GET Request No certificate version
	* @param 
	* @		strUrl: 	The input parameters, the requested Url address, such as: http://www.baidu.com
	* @ 	strResponse:The output parameters, result content
	* @ 	pCaPath:  	The input parameters for the path of the CA certificate. If the input is NULL, not to verify the validity of the certificate on the server.
	* @return Returns the POST whether successful
	*/
	int Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath = NULL);
public:
	zlog_category_t *category;

public:
	static std::string FACE_KEY;
	static std::string FACE_SECRET;

	static std::string URL_DETECT; 
	static std::string URL_COMPARE; 
	static std::string URL_RECOGNIZE; 
	static std::string URL_IDENTIFY;
	static std::string URL_SEARCH; 
	static std::string URL_TRAIN; 
	static std::string URL_VERIFY; 

	static std::string URL_PERSON_ADDFACE;
	static std::string URL_PERSON_CREATE;
	static std::string URL_PERSON_DELETE;
	static std::string URL_PERSON_GETINFO;
	static std::string URL_PERSON_REMOVEFACE;
	static std::string URL_PERSON_SETINFO;

	static std::string URL_GROUP_ADDPERSON;
	static std::string URL_GROUP_CREATE;
	static std::string URL_GROUP_DELETE;
	static std::string URL_GROUP_GETINFO;
	static std::string URL_GROUP_REMOVEPERSON;
	static std::string URL_GROUP_SETINFO;

	static std::string URL_INFO_GETAPP;
	static std::string URL_INFO_GETFACE;
	static std::string URL_INFO_GETGROUPLIST;
	static std::string URL_INFO_GETIMAGE;
	static std::string URL_INFO_GETPERSONLIST;
	static std::string URL_INFO_GETQUOTA;
	static std::string URL_INFO_GETSESSION;
	static std::string URL_INFO_GET_FACESETLIST;

	static std::string URL_FACESET_CREATE;
	static std::string URL_FACESET_DELETE;
	static std::string URL_FACESET_ADDFACE;
	static std::string URL_FACESET_REMOVEFACE;
	static std::string URL_FACESET_SETINFO;
	static std::string URL_FACESET_GET_INFO;

	static std::string URL_TRAIN_VERIFY;
	static std::string URL_TRAIN_SEARCH;
	static std::string URL_TRAIN_IDENTIFY;
	static std::string URL_GROUPING_GROUPING;
};

#endif
