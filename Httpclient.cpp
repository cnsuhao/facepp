#include "httpclient.h"
#include "curl/curl.h"
#include <string>

std::string HttpClient::FACE_KEY					= "you key";
std::string HttpClient::FACE_SECRET					= "you secret";
std::string HttpClient::URL_DETECT					= "http://apicn.faceplusplus.com/v2/detection/detect"; 
std::string HttpClient::URL_COMPARE					= "http://apicn.faceplusplus.com/v2/recognition/compare"; 
std::string HttpClient::URL_RECOGNIZE				= "http://apicn.faceplusplus.com/v2/recognition/recognize"; 
std::string HttpClient::URL_SEARCH					= "http://apicn.faceplusplus.com/v2/recognition/search"; 
std::string HttpClient::URL_TRAIN					= "http://apicn.faceplusplus.com/v2/recognition/train"; 
std::string HttpClient::URL_VERIFY					= "http://apicn.faceplusplus.com/v2/recognition/verify"; 

std::string HttpClient::URL_PERSON_ADDFACE			= "http://apicn.faceplusplus.com/v2/person/add_face";
std::string HttpClient::URL_PERSON_CREATE			= "http://apicn.faceplusplus.com/v2/person/create";
std::string HttpClient::URL_PERSON_DELETE			= "http://apicn.faceplusplus.com/v2/person/delete";
std::string HttpClient::URL_PERSON_GETINFO			= "http://apicn.faceplusplus.com/v2/person/get_info";
std::string HttpClient::URL_PERSON_REMOVEFACE		= "http://apicn.faceplusplus.com/v2/person/remove_face";
std::string HttpClient::URL_PERSON_SETINFO			= "http://apicn.faceplusplus.com/v2/person/set_info";

std::string HttpClient::URL_GROUP_ADDPERSON			= "http://apicn.faceplusplus.com/v2/group/add_person";
std::string HttpClient::URL_GROUP_CREATE			= "http://apicn.faceplusplus.com/v2/group/create";
std::string HttpClient::URL_GROUP_DELETE			= "http://apicn.faceplusplus.com/v2/group/delete";
std::string HttpClient::URL_GROUP_GETINFO			= "http://apicn.faceplusplus.com/v2/group/get_info";
std::string HttpClient::URL_GROUP_REMOVEPERSON		= "http://apicn.faceplusplus.com/v2/group/remove_person";
std::string HttpClient::URL_GROUP_SETINFO			= "http://apicn.faceplusplus.com/v2/group/set_info";

std::string HttpClient::URL_INFO_GETAPP				= "http://apicn.faceplusplus.com/v2/info/get_app";
std::string HttpClient::URL_INFO_GETFACE			= "http://apicn.faceplusplus.com/v2/info/get_face";
std::string HttpClient::URL_INFO_GETGROUPLIST		= "http://apicn.faceplusplus.com/v2/info/get_group_list";
std::string HttpClient::URL_INFO_GETIMAGE			= "http://apicn.faceplusplus.com/v2/info/get_image";
std::string HttpClient::URL_INFO_GETPERSONLIST		= "http://apicn.faceplusplus.com/v2/info/get_person_list";
std::string HttpClient::URL_INFO_GETQUOTA			= "http://apicn.faceplusplus.com/v2/info/get_quota";
std::string HttpClient::URL_INFO_GETSESSION			= "http://apicn.faceplusplus.com/v2/info/get_session";
std::string HttpClient::URL_INFO_GET_FACESETLIST	= "http://apicn.faceplusplus.com/v2/info/get_faceset_list";

std::string HttpClient::URL_FACESET_CREATE			= "http://apicn.faceplusplus.com/v2/faceset/create";
std::string HttpClient::URL_FACESET_DELETE			= "http://apicn.faceplusplus.com/v2/faceset/delete";
std::string HttpClient::URL_FACESET_ADDFACE			= "http://apicn.faceplusplus.com/v2/faceset/add_face";
std::string HttpClient::URL_FACESET_REMOVEFACE		= "http://apicn.faceplusplus.com/v2/faceset/remove_face";
std::string HttpClient::URL_FACESET_SETINFO			= "http://apicn.faceplusplus.com/v2/faceset/set_info";
std::string HttpClient::URL_FACESET_GET_INFO		= "http://apicn.faceplusplus.com/v2/faceset/get_info";

std::string HttpClient::URL_TRAIN_VERIFY			= "http://apicn.faceplusplus.com/v2/train/verify";
std::string HttpClient::URL_TRAIN_SEARCH			= "http://apicn.faceplusplus.com/v2/train/search";
std::string HttpClient::URL_TRAIN_IDENTIFY			= "http://apicn.faceplusplus.com/v2/train/identify";
std::string HttpClient::URL_GROUPING_GROUPING		= "http://apicn.faceplusplus.com/v2/grouping/grouping";

HttpClient::HttpClient(void)
{

}

HttpClient::~HttpClient(void)
{

}

static size_t m_read_callback(void* ptr, size_t size, size_t nmemb, void* stream)
{
    curl_off_t nread;
    /* in real-world cases, this would probably get this data differently
       as this fread() stuff is exactly what the library already would do
       by default internally */ 
    size_t retcode = fread(ptr, size, nmemb, (FILE *)stream);
    nread = (curl_off_t)retcode;
    std::cout << "read " << nread << " bytes from file" << std::endl;
    return retcode;
}

static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
	std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
	if( NULL == str || NULL == buffer )
	{
		return -1;
	}

    char* pData = (char*)buffer;
	cout << "accept data is: " << pData << endl;
    str->append(pData, size * nmemb);
	return nmemb;
}


std::string HttpClient::ftp_upload(std::string filename, 
                       std::string username, 
                       std::string password, 
                       std::string ftp_url) 
{
    CURL* curl = NULL;
    CURLcode res;
    FILE* hd_src = NULL;
    struct stat file_info;
    curl_off_t fsize;
    std::string http_url = "http://facerec.b0.upaiyun.com/tmp/" + filename;

    if (stat(filename.c_str(), &file_info)) 
        throw std::string("fail to get file info");
    fsize = (curl_off_t)file_info.st_size;

    hd_src = fopen(filename.c_str(), "rb");
    if (hd_src == NULL) 
        throw std::string("fail to open file");

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, m_read_callback);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_URL, (ftp_url + filename).c_str());
        curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) 
            std::cout << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
    }

    if (hd_src) 
    {
        fclose(hd_src);
        hd_src = NULL;
    }

    curl_global_cleanup();

    return http_url;
}


void EasyCurl_file(const std::string & strUrl, std::string fileName)
{
	struct curl_httppost *formpost=NULL;
	struct curl_httppost *lastptr=NULL;
	
	CURL* curl = curl_easy_init();

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key", 
		CURLFORM_COPYCONTENTS, "private key", 
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret", 
		CURLFORM_COPYCONTENTS, "own secret",

#if 0
    // Upload a file, specifies the full path to the local file
    curl_formadd(&pFormPost, &pLastElem, 
        CURLFORM_COPYNAME, "ufile01", 
        CURLFORM_FILE, "C:\\temp\\upload_test_curl_cswuyg.txt", 
        CURLFORM_CONTENTTYPE, "application/octet-stream", 
        CURLFORM_END);
#endif

	char* file_data = NULL;
	long file_size = 0;
	
	FILE* fp = fopen(fileName.c_str(), "rb");
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
		CURLFORM_COPYNAME, "img",				// Upload the field key name
		CURLFORM_BUFFER, "test.jpg",			// Specify name of the file in service side; It is used to tell libcurl file content already in the cache
		CURLFORM_BUFFERPTR, file_data,			// file data
		CURLFORM_BUFFERLENGTH, file_size,		// Specify the file size
		CURLFORM_CONTENTTYPE, "image/jpeg",		// Specify the upload file type
		CURLFORM_END);
		
	string HTTPRESULT;
	if(curl) {
		/* what URL that receives this POST */ 
		// Set related parameters of the request to make curl agreement or returns the specified data
		curl_easy_setopt(curl, CURLOPT_URL, strUrl);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);				// to upload a file with URL
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &HTTPRESULT);			// The object pointer data storage, such as string HTTPRESULT
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);		// Set the callback function when the result data arrived

		char error[1024];
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error);				// set error buffer for error messages

		res = curl_easy_perform(curl);
		if(res != CURLE_OK) cout<<endl<<error<<endl;
	}
	curl_easy_cleanup(curl);
	curl_formfree(formpost);
	cout<<endl<<HTTPRESULT<<endl;

	if(file_data != NULL)
		delete [] file_data;
}

int HttpClient::Post(const std::string & strUrl, const std::map<std::string,std::string> & mapPost, std::string & strResponse)
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

int HttpClient::Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse)
{
	CURLcode res;
	CURL* curl = curl_easy_init();
	if(NULL == curl)
	{
		return CURLE_FAILED_INIT;
	}
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
	curl_easy_cleanup(curl);
	return res;
}

int HttpClient::Get(const std::string & strUrl, std::string & strResponse)
{
	CURLcode res;
	CURL* curl = curl_easy_init();
	if(NULL == curl)
	{
		return CURLE_FAILED_INIT;
	}
	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	/**
    * When multiple threads are using timeout handling, at the same time, the main thread of sleep 
    * or wait operation.If you do not set this option, libcurl will signal to interrupt the wait resulting in program exits.
	*/
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return res;
}

int HttpClient::Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath)
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
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
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

int HttpClient::Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath)
{
	CURLcode res;
	CURL* curl = curl_easy_init();
	if(NULL == curl)
	{
		return CURLE_FAILED_INIT;
	}
	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	if(NULL == pCaPath)
	{
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
	}
	else
	{
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);
	}
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return res;
}


int main (void)
