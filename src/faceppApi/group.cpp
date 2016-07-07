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
#include "group.h"
#include "http_get.h"

namespace fpp {

group::group(std::string cfgfile) 
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

group::~group() { m_groups.clear(); }

std::vector<group_t> group::get_groups()  
{
    try 
    {
        std::string json = http_get(m_options["SERVER"] +                         
                                    m_options["VERSION"] +                        
                                    std::string("/info/get_group_list?api_secret=") + 
                                    m_options["API_SECRET"] +                     
                                    "&api_key=" +                               
                                    m_options["API_KEY"]);
        Json::Reader reader;                                                    
        Json::Value root;                                                       
        Json::Value groups;                                                      
        unsigned int i;                                                         
                                                                                
        reader.parse(json, root, false);                                        
        groups = root["group"];                                                   
        for (i = 0; i < groups.size(); i++) 
        {
            group_t g;
            g.id = groups[i]["group_id"].asString();
            g.name = groups[i]["group_name"].asString();
            g.tag = groups[i]["tag"].asString();

            m_groups.push_back(g);
        }
    } 
    catch (std::string ex) 
    {
        std::cout << ex << std::endl;
    }
    return m_groups;
}

unsigned int group::size() const 
{
    return m_groups.size();
}

group_t group::get_group(unsigned int index) 
{
    std::vector<group_t>::iterator iter;
    unsigned int i = 1;

    if (m_groups.size() == 0) 
        throw std::string("no group");

    if (m_groups.size() < index) 
        throw std::string("index is out of range");

    for (iter = m_groups.begin(); iter != m_groups.end(); iter++, i++) 
    {
        if (i == index) 
            return *iter;
    }
}

void group::create(std::string name) 
{
    try 
    {
        http_get(m_options["SERVER"] +                       
                 m_options["VERSION"] +                      
                 std::string("/group/create?api_secret=") + 
                 m_options["API_SECRET"] +                   
                 "&api_key=" +                               
                 m_options["API_KEY"] + 
                 "&group_name=" + 
                 name);
    } 
    catch (std::string ex) 
    {
        std::cout << ex << std::endl;
    }
}

void group::create(std::string name, std::string tag) 
{

}

void group::remove(std::string name) 
{
    try                                                                         
    {                                                                           
        http_get(m_options["SERVER"] +                                          
                 m_options["VERSION"] +                                         
                 std::string("/group/delete?api_secret=") +                    
                 m_options["API_SECRET"] +                                      
                 "&api_key=" +                                                  
                 m_options["API_KEY"] +                                         
                 "&group_name=" +                                              
                 name);                                                         
    }                                                                           
    catch (std::string ex)                                                      
    {                                                                           
        std::cout << ex << std::endl;                                           
    }
}

void group::add_person(std::string group_name, std::string person_name) 
{                                                                               
    try                                                                         
    {                                                                           
        http_get(m_options["SERVER"] +                                          
                 m_options["VERSION"] +                                         
                 std::string("/group/add_person?api_secret=") +                     
                 m_options["API_SECRET"] +                                      
                 "&api_key=" +                                                  
                 m_options["API_KEY"] + 
                 "&person_name=" + 
                 person_name +             
                 "&group_name=" +                                               
                 group_name);                                                         
    }                                                                           
    catch (std::string ex)                                                      
    {                                                                           
        std::cout << ex << std::endl;                                           
    }                                                                           
}

void group::add_person(std::string group_name, 
                       std::vector<std::string> person_names) 
{

}

}
