/*                                                                              
 * Copyright (C)                                                  
 *                                                               
 *                                                                              
 * Author:                              
 * Maintainer:                        
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
#include "detect.h"
#include "read_cfg.h"
#include "http_get.h"

namespace fpp {

detect::detect(std::string url, std::string cfgfile) 
{
    try 
    {
        std::map<std::string, std::string> options = get_options(cfgfile);
        std::string json = http_get(options["SERVER"] + 
                                    options["VERSION"] + 
                                    std::string("/detection/detect?url=") + 
                                    url + 
                                    "&api_secret=" + 
                                    options["API_SECRET"] + 
                                    "&api_key=" + 
                                    options["API_KEY"]);
        Json::Reader reader;
        Json::Value root;
        Json::Value faces;
        unsigned int i;

        reader.parse(json, root, false);
        faces = root["face"];
        for (i = 0; i < faces.size(); i++) 
        {
            age_t age;
            age.range = faces[i]["attribute"]["age"]["range"].asUInt();
            age.value = faces[i]["attribute"]["age"]["value"].asUInt();
            
            gender_t gender;
            gender.confidence = faces[i]["attribute"]["gender"]["confidence"].asFloat();
            gender.value = faces[i]["attribute"]["gender"]["value"].asString();
            
            race_t race;
            race.confidence = faces[i]["attribute"]["race"]["confidence"].asFloat();
            race.value = faces[i]["attribute"]["race"]["value"].asString();
            
            attribute_t attribute;
            attribute.age = age;
            attribute.gender = gender;
            attribute.race = race;
            attribute.smiling = faces[i]["attribute"]["smiling"]["value"].asFloat();
            
            face_t face;
            face.attribute = attribute;
            face.face_id = faces[i]["face_id"].asString();
           
            position_t position;
            point_t center;
            center.x = faces[i]["position"]["center"]["x"].asFloat();
            center.y = faces[i]["position"]["center"]["y"].asFloat();
            position.center = center;
            point_t eye_left;
            eye_left.x = faces[i]["position"]["eye_left"]["x"].asFloat();
            eye_left.y = faces[i]["position"]["eye_left"]["y"].asFloat();
            position.eye_left = eye_left;
            point_t eye_right;
            eye_right.x = faces[i]["position"]["eye_right"]["x"].asFloat();
            eye_right.y = faces[i]["position"]["eye_right"]["y"].asFloat();
            position.eye_right = eye_right;
            position.height = faces[i]["position"]["height"].asFloat();
            point_t mouth_left;                                                   
            mouth_left.x = faces[i]["position"]["mouth_left"]["x"].asFloat();          
            mouth_left.y = faces[i]["position"]["mouth_left"]["y"].asFloat();          
            position.mouth_left = mouth_left;
            point_t mouth_right;                                                  
            mouth_right.x = faces[i]["position"]["mouth_right"]["x"].asFloat();        
            mouth_right.y = faces[i]["position"]["mouth_right"]["y"].asFloat();        
            position.mouth_right = mouth_right;
            point_t nose;                                                     
            nose.x = faces[i]["position"]["nose"]["x"].asFloat();           
            nose.y = faces[i]["position"]["nose"]["y"].asFloat();           
            position.nose = nose;
            position.width = faces[i]["position"]["width"].asFloat();
            face.position = position;

            m_faces.push_back(face);
        }
    } 
    catch (std::string ex) 
    {
        std::cout << ex << std::endl;
    }
}

detect::~detect() { m_faces.clear(); }

std::vector<face_t> detect::get_faces() const 
{
    return m_faces;
}

unsigned int detect::size() const 
{
    return m_faces.size();
}

face_t detect::get_face(unsigned int index) 
{
    std::vector<face_t>::iterator iter;
    unsigned int i = 1;

    if (m_faces.size() == 0) 
        throw std::string("no face");

    if (m_faces.size() < index) 
        throw std::string("index is out of range");

    for (iter = m_faces.begin(); iter != m_faces.end(); iter++, i++) 
    {
        if (i == index) 
            return *iter;
    }
}

}
