//
//  Camera.cpp
//  modules
//
//  Created by Guanlun Zhao on 11/29/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "Camera.hpp"

#include <iostream>
using namespace std;

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

void Camera::rotateCamera(int xDiff, int yDiff) {
    glm::vec3 viewDir = glm::normalize(this->lookAtPos - this->cameraPos);
    
    float x = viewDir[0];
    float z = viewDir[1];
    float y = viewDir[2];
    
    float xyPlaneProjLen = sqrt(x * x + y * y);
    
    float theta = atan2(xyPlaneProjLen, z);
    float phi = atan2(y, x);
    
    theta += yDiff * 0.002;
    phi += xDiff * 0.002;
    
    float newXyPlaneProjLen = sin(theta);

    viewDir[0] = newXyPlaneProjLen * cos(phi);
    viewDir[1] = cos(theta);
    viewDir[2] = newXyPlaneProjLen * sin(phi);
    
    this->lookAtPos = this->cameraPos + viewDir;
    
    this->updateViewMatrix();
}
