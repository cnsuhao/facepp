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
#include "train.h"
#include "http_get.h"

namespace fpp {

train::train(std::string cfgfile) 
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

train::~train() 
{

}

void train::verify(std::string person_name) 
{                                                                               
    try                                                                         
    {                                                                           
        http_get(m_options["SERVER"] +                                          
                 m_options["VERSION"] +                                         
                 std::string("/train/verify?api_secret=") +                     
                 m_options["API_SECRET"] +                                      
                 "&api_key=" +                                                  
                 m_options["API_KEY"] + 
                 "&person_name=" + 
                 person_name);                                                         
    }                                                                           
    catch (std::string ex)                                                      
    {                                                                           
        std::cout << ex << std::endl;                                           
    }                                                                           
}

}
