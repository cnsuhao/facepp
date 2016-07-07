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
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <json/json.h>
#include "recognition.h"
#include "http_get.h"
#include "http_post.h"
#include "zlog.h"

#define LOG_TAG	zlog_get_category("recognition")

namespace fpp {

recognition::recognition(std::string cfgfile) 
{
    try 
    {
        m_options = get_options(cfgfile);
    } 
    catch (std::string ex) 
    {
        std::cout << ex << std::endl;
    }
}

recognition::~recognition() 
{

}

std::vector<candidate_t> recognition::identify(std::string url, std::string group_name) 
{    
	//LOGD("SERVER:%s",  m_options["SERVER"].c_str());
	//LOGD("API_KEY:%s", m_options["API_KEY"].c_str());
	//LOGD("API_SECRET:%s", m_options["API_SECRET"].c_str());
	//LOGD("SERVER:%s/%s", m_options["SERVER"].c_str(),m_options["VERSION"].c_str());

	try                                                                         
    { 
#ifdef HTTP_GET     
        std::string json = http_get(m_options["SERVER"] +                                          
                                    m_options["VERSION"] + 
                                    std::string("/recognition/identify?url=") + 
                                    url + 
                                    "&api_secret=" + 
                                    m_options["API_SECRET"] + 
                                    "&api_key=" + 
                                    m_options["API_KEY"] + 
                                    "&group_name=" + 
                                    group_name);
#else
        std::string json = post(m_options["SERVER"] +                                          
                                    m_options["VERSION"] + 
                                    std::string("/recognition/identify"), 
                                    "api_secret=" + m_options["API_SECRET"] +   
                                    "&api_key=" + m_options["API_KEY"] + 
                                    "&group_name=" + group_name +
                                    "&url=" + url
                                    );
#endif
		LOGD("json:%s",  json.c_str());
        Json::Reader reader;                                                    
        Json::Value root;                                                       
        Json::Value faces;                                                      
        unsigned int i, j;                                                       
                                                                                
        reader.parse(json, root, false);                                        
        faces = root["face"];
		//printf("faces.size() = %d\n", faces.size());
        for (i = 0; i < faces.size(); i++) 
        {
            Json::Value candidates = faces[i]["candidate"];
            for (j = 0; j < candidates.size(); j++) 
            {
                candidate_t candidate;
                candidate.confidence = candidates[j]["confidence"].asFloat();
                candidate.person_id = candidates[j]["person_id"].asString();
                candidate.person_name = candidates[j]["person_name"].asString();
                candidate.tag = candidates[j]["tag"].asString();
                m_candidates.push_back(candidate);
            }
        }
    }                                                                           
    catch (std::string ex)                                                      
    {                                                                           
        std::cout << ex << std::endl; 
    }                        
    return m_candidates;    
}

candidate_t recognition::get_confident_candidate(std::vector<candidate_t> candidates) 
{
    std::vector<candidate_t>::iterator iter;
    float confidence = 0.0f;
    candidate_t confident_candidate;

    for (iter = m_candidates.begin(); iter != m_candidates.end(); iter++) 
    {
        if (confidence < (*iter).confidence) 
        {
            confidence = (*iter).confidence;
            confident_candidate = *iter;
        }
    }

    return confident_candidate;
}

}
