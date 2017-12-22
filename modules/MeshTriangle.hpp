//
//  MeshTriangle.hpp
//  modules
//
//  Created by Guanlun Zhao on 12/22/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#ifndef MeshTriangle_hpp
#define MeshTriangle_hpp

#include <glm/glm.hpp>

class MeshTriangle {
public:
    MeshTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
    
    float intersectRay(glm::vec3 rayStartPos, glm::vec3 rayDir) const;
private:
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;
    
    glm::vec3 e1;
    glm::vec3 e2;
    glm::vec3 normal;
};

#endif /* MeshTriangle_hpp */
