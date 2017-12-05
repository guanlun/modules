//
//  Light.hpp
//  modules
//
//  Created by Guanlun Zhao on 12/3/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light {
public:
    Light(glm::vec3 pos) : position(pos) {};
    
private:
    glm::vec3 position;
};

#endif /* Light_hpp */
