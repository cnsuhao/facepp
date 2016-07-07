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

#include <iostream>
#include <json/json.h>
#include "faceset.h"
#include "http_get.h"

namespace fpp {

faceset::faceset(std::string cfgfile) 
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

faceset::~faceset() { m_facesets.clear(); }

std::vector<faceset_t> faceset::get_facesets()  
{
    try 
    {
        std::string json = http_get(m_options["SERVER"] +                         
                                    m_options["VERSION"] +                        
                                    std::string("/info/get_faceset_list?api_secret=") + 
                                    m_options["API_SECRET"] +                     
                                    "&api_key=" +                               
                                    m_options["API_KEY"]);
        Json::Reader reader;                                                    
        Json::Value root;                                                       
        Json::Value facesets;                                                      
        unsigned int i;                                                         
                                                                                
        reader.parse(json, root, false);                                        
        facesets = root["faceset"];                                                   
        for (i = 0; i < facesets.size(); i++) 
        {
            faceset_t fs;
            fs.id = facesets[i]["faceset_id"].asString();
            fs.name = facesets[i]["faceset_name"].asString();
            fs.tag = facesets[i]["tag"].asString();

            m_facesets.push_back(fs);
        }
    } 
    catch (std::string ex) 
    {
        std::cout << ex << std::endl;
    }
    return m_facesets;
}

unsigned int faceset::size() const 
{
    return m_facesets.size();
}

faceset_t faceset::get_faceset(unsigned int index) 
{
    std::vector<faceset_t>::iterator iter;
    unsigned int i = 1;

    if (m_facesets.size() == 0) 
        throw std::string("no faceset");

    if (m_facesets.size() < index) 
        throw std::string("index is out of range");

    for (iter = m_facesets.begin(); iter != m_facesets.end(); iter++, i++) 
    {
        if (i == index) 
            return *iter;
    }
}

void faceset::create(std::string name) 
{
    try 
    {
        http_get(m_options["SERVER"] +                       
                 m_options["VERSION"] +                      
                 std::string("/faceset/create?api_secret=") + 
                 m_options["API_SECRET"] +                   
                 "&api_key=" +                               
                 m_options["API_KEY"] + 
                 "&faceset_name=" + 
                 name);
    } 
    catch (std::string ex) 
    {
        std::cout << ex << std::endl;
    }
}

void faceset::create(std::string name, std::string tag) 
{

}

void faceset::remove(std::string name) 
{
    try                                                                         
    {                                                                           
        http_get(m_options["SERVER"] +                                          
                 m_options["VERSION"] +                                         
                 std::string("/faceset/delete?api_secret=") +                    
                 m_options["API_SECRET"] +                                      
                 "&api_key=" +                                                  
                 m_options["API_KEY"] +                                         
                 "&faceset_name=" +                                              
                 name);                                                         
    }                                                                           
    catch (std::string ex)                                                      
    {                                                                           
        std::cout << ex << std::endl;                                           
    }
}

void faceset::add_face(std::string faceset_name, std::string face_id) 
{                                                                               
    try                                                                         
    {                                                                           
        http_get(m_options["SERVER"] +                                          
                 m_options["VERSION"] +                                         
                 std::string("/faceset/add_face?api_secret=") +                     
                 m_options["API_SECRET"] +                                      
                 "&api_key=" +                                                  
                 m_options["API_KEY"] + 
                 "&face_id=" + 
                 face_id +             
                 "&faceset_name=" +                                               
                 faceset_name);                                                         
    }                                                                           
    catch (std::string ex)                                                      
    {                                                                           
        std::cout << ex << std::endl;                                           
    }                                                                           
}

void faceset::add_face(std::string faceset_name, 
                       std::vector<std::string> face_id) 
{

}

}
