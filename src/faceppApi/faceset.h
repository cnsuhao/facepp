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

#ifndef FACESET_H
#define FACESET_H

#include <string>
#include <vector>
#include "read_cfg.h"

namespace fpp {

typedef struct {
    std::string id;
    std::string name;
    std::string tag;
} faceset_t;

class faceset {
public:
    faceset(std::string cfgfile);
    ~faceset();

public:
    std::vector<faceset_t> get_facesets();
    faceset_t get_faceset(unsigned int index);
    unsigned int size() const;
    void create(std::string name);
    void create(std::string name, std::string tag);
    void remove(std::string name);
    void add_face(std::string faceset_name, std::string face_id);
    void add_face(std::string faceset_name, 
                  std::vector<std::string> face_id);

private:
    std::map<std::string, std::string> m_options;
    std::vector<faceset_t> m_facesets;
};

}

#endif /* FACESET_H */
