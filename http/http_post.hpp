#ifndef HTTP_POST_H
#define HTTP_POST_H

#include <string>

namespace fpp 
{

class chunk
{ 
public:
    static size_t handle(char* data, size_t size, size_t nmemb, void* p);
    std::string get_content();

private:
    std::string m_content;
    size_t m_handle_impl(char* data, size_t size, size_t nmemb);
};

std::string http_post(std::string url);

}

#endif

