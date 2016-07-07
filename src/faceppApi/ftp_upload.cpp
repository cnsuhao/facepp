/*                                                                              
 * Copyright (C) 2013 Deepin, Inc.                                       
 *               2013 Zhai Xiang                                         
 *                                                                              
 * Author:     Zhai Xiang <zhaixiang@linuxdeepin.com>                           
 * Maintainer: Zhai Xiang <zhaixiang@linuxdeepin.com>                           
 *                                                                              
 * This program is free software: you can redistribute it and/or modify         
 * it under the terms of the GNU General Public License as published by         
 * the Free Software Foundation, either version 3 of the License, or            
 * any later version.                                                           
 *                                                                              
 * This program is distributed in the hope that it will be useful,              
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
 * GNU General Public License for more details.                                 
 *                                                                              
 * You should have received a copy of the GNU General Public License            
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        
 */

#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include "ftp_upload.h"

namespace fpp 
{

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

std::string ftp_upload(std::string filename, 
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

}
