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
    Camera(glm::vec3 position);
    glm::mat4 getViewProjectionMatrix() const;
    
    inline glm::mat4 getViewMatrix() const { return this->viewMtx; };
    inline void setViewMatrix(const glm::mat4 viewMtx) { this->viewMtx = viewMtx; };
    
    void moveCamera(int direction);
    
    void rotateCamera(int xDiff, int yDiff);
    
protected:
    void updateViewMatrix();
    
    glm::mat4 projectionMtx;
    glm::mat4 viewMtx;
    
    glm::vec3 lookAtPos;
    glm::vec3 cameraPos;
};

#endif /* Camera_hpp */
