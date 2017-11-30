//
//  Camera.cpp
//  modules
//
//  Created by Guanlun Zhao on 11/29/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera() {
    this->projectionMtx = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    this->viewMtx = glm::lookAt(
        glm::vec3(4, 3, 3),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
}

glm::mat4 Camera::getViewProjectionMatrix() const {
    return this->projectionMtx * this->viewMtx;
}
