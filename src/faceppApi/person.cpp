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
#include "person.h"
#include "http_get.h"

namespace fpp {

person::person(std::string cfgfile) 
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

person::~person() { m_persons.clear(); }

std::vector<person_t> person::get_persons()  
{
    try 
    {
        std::string json = http_get(m_options["SERVER"] +                         
                                    m_options["VERSION"] +                        
                                    std::string("/info/get_person_list?api_secret=") + 
                                    m_options["API_SECRET"] +                     
                                    "&api_key=" +                               
                                    m_options["API_KEY"]);
        Json::Reader reader;                                                    
        Json::Value root;                                                       
        Json::Value persons;                                                      
        unsigned int i;                                                         
                                                                                
        reader.parse(json, root, false);                                        
        persons = root["person"];                                                   
        for (i = 0; i < persons.size(); i++) 
        {
            person_t p;
            p.id = persons[i]["person_id"].asString();
            p.name = persons[i]["person_name"].asString();
            p.tag = persons[i]["tag"].asString();

            m_persons.push_back(p);
        }
    } 
    catch (std::string ex) 
    {
        std::cout << ex << std::endl;
    }
    return m_persons;
}

unsigned int person::size() const 
{
    return m_persons.size();
}

person_t person::get_person(unsigned int index) 
{
    std::vector<person_t>::iterator iter;
    unsigned int i = 1;

    if (m_persons.size() == 0) 
        throw std::string("no person");

    if (m_persons.size() < index) 
        throw std::string("index is out of range");

    for (iter = m_persons.begin(); iter != m_persons.end(); iter++, i++) 
    {
        if (i == index) 
            return *iter;
    }
}

void person::create(std::string name) 
{
    try 
    {
        http_get(m_options["SERVER"] +                       
                 m_options["VERSION"] +                      
                 std::string("/person/create?api_secret=") + 
                 m_options["API_SECRET"] +                   
                 "&api_key=" +                               
                 m_options["API_KEY"] + 
                 "&person_name=" + 
                 name);
    } 
    catch (std::string ex) 
    {
        std::cout << ex << std::endl;
    }
}

void person::create(std::string name, std::string tag) 
{

}

void person::remove(std::string name) 
{
    try                                                                         
    {                                                                           
        http_get(m_options["SERVER"] +                                          
                 m_options["VERSION"] +                                         
                 std::string("/person/delete?api_secret=") +                    
                 m_options["API_SECRET"] +                                      
                 "&api_key=" +                                                  
                 m_options["API_KEY"] +                                         
                 "&person_name=" +                                              
                 name);                                                         
    }                                                                           
    catch (std::string ex)                                                      
    {                                                                           
        std::cout << ex << std::endl;                                           
    }
}

}
