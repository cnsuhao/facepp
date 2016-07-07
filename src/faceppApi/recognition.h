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

#ifndef RECOGNITION_H
#define RECOGNITION_H

#include <string>
#include <vector>
#include "read_cfg.h"

namespace fpp {

typedef struct {
    float confidence;
    std::string person_id;
    std::string person_name;
    std::string tag;
} candidate_t;

class recognition {
public:
    recognition(std::string cfgfile);
    ~recognition();

public:
    std::vector<candidate_t> identify(std::string url, std::string group_name);
    candidate_t get_confident_candidate(std::vector<candidate_t> candidates);

private:
    std::map<std::string, std::string> m_options;
    std::vector<candidate_t> m_candidates;
};

}

#endif /* RECOGNITION_H */
