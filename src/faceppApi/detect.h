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

#ifndef DETECT_H
#define DETECT_H

#include <string>
#include <vector>

namespace fpp {

typedef struct {
    unsigned int range;
    unsigned int value;
} age_t;

typedef struct {
    float confidence;
    std::string value;
} gender_t;

typedef struct {
    float confidence;
    std::string value;
} race_t;

typedef struct {
    age_t age;
    gender_t gender;
    race_t race;
    float smiling;
} attribute_t;

typedef struct {
    float x;
    float y;
} point_t;

typedef struct {
    point_t center;
    point_t eye_left;
    point_t eye_right;
    float height;
    point_t mouth_left;
    point_t mouth_right;
    point_t nose;
    float width;
} position_t;

typedef struct {
    attribute_t attribute;
    std::string face_id;
    position_t position;
} face_t;

class detect {
public:
    detect(std::string url, std::string cfgfile);
    ~detect();

public:
    std::vector<face_t> get_faces() const;
    face_t get_face(unsigned int index);
    unsigned int size() const;

private:
    std::vector<face_t> m_faces;
    unsigned int m_img_height;
    std::string m_img_id;
    unsigned int m_img_width;
    std::string m_session_id;
    std::string m_url;
};

}

#endif /* DETECT_H */
