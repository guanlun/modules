//
//  Camera.hpp
//  modules
//
//  Created by Guanlun Zhao on 11/29/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();
    glm::mat4 getViewProjectionMatrix() const;
    
    inline glm::mat4 getViewMatrix() const { return this->viewMtx; };
    inline void setViewMatrix(const glm::mat4 viewMtx) { this->viewMtx = viewMtx; };
private:
    glm::mat4 projectionMtx;
    glm::mat4 viewMtx;
};

#endif /* Camera_hpp */
