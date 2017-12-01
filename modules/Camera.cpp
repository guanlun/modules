//
//  Camera.cpp
//  modules
//
//  Created by Guanlun Zhao on 11/29/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(glm::vec3 position) {
    this->projectionMtx = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    this->lookAtPos = glm::vec3(0, 0, 0);
    this->cameraPos = position;
    
    this->updateViewMatrix();
}

glm::mat4 Camera::getViewProjectionMatrix() const {
    return this->projectionMtx * this->viewMtx;
}

void Camera::updateViewMatrix() {
    this->viewMtx = glm::lookAt(
        this->cameraPos,
        this->lookAtPos,
        glm::vec3(0, 1, 0)
    );
}

void Camera::moveCamera(int direction) {
    switch ((char)direction) {
        case 'W':
            this->cameraPos[1] += 0.1;
            break;
            
        case 'A':
            this->cameraPos[0] -= 0.1;
            break;
            
        case 'S':
            this->cameraPos[1] -= 0.1;
            break;
            
        case 'D':
            this->cameraPos[0] += 0.1;
            break;
    }
    
    this->updateViewMatrix();
}
