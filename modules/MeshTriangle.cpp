//
//  MeshTriangle.cpp
//  modules
//
//  Created by Guanlun Zhao on 12/22/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "MeshTriangle.hpp"

#define EPSILON 0.00001

MeshTriangle::MeshTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
:v1(v1), v2(v2), v3(v3) {
    this->e1 = v2 - v1;
    this->e2 = v3 - v1;
    this->normal = glm::normalize(glm::cross(this->e2, this->e1));
}

float MeshTriangle::intersectRay(glm::vec3 rayStartPos, glm::vec3 rayDir) const {
    glm::vec3 P = glm::cross(rayDir, this->e2);
    float det = glm::dot(this->e1, P);
    
    if (det > -EPSILON && det < EPSILON) {
        return -1.f;
    }
    
    float invDet = 1.f / det;
    
    glm::vec3 T = rayStartPos - this->v1;
    float u = glm::dot(T, P) * invDet;
    
    if (u < 0.f || u > 1.f) {
        return -1.f;
    }
    
    glm::vec3 Q = glm::cross(T, this->e1);
    float v = glm::dot(rayDir, Q) * invDet;
    
    if (v < 0.f || u + v > 1.f) {
        return -1.f;
    }
    
    float t = glm::dot(this->e2, Q) * invDet;
    
    if (t > EPSILON) {
        return t;
    } else {
        return -1.f;
    }
}
