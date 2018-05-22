//
//  SceneObject.cpp
//  modules
//
//  Created by Guanlun Zhao on 11/27/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "SceneObject.hpp"

SceneObject::SceneObject(ObjectData objData, glm::vec3 pos) {
    this->position = pos;
    this->modelMatrix = glm::translate(glm::mat4(1.0f), pos);
    
    const vector<GLfloat>& vertexPositions = objData.vertexPositionData;
    for (int i = 0; i < vertexPositions.size(); i += 9) {
//        this->vertices.push_back(MeshTriangle(glm::vec3(vertexPositions[i], vertexPositions[i + 1], vertexPositions[i + 2])));
        glm::vec3 v1(vertexPositions[i], vertexPositions[i + 1], vertexPositions[i + 2]);
        glm::vec3 v2(vertexPositions[i + 3], vertexPositions[i + 4], vertexPositions[i + 5]);
        glm::vec3 v3(vertexPositions[i + 6], vertexPositions[i + 7], vertexPositions[i + 8]);
        
        this->triangles.push_back(MeshTriangle(v1, v2, v3));
    }
    
    glGenBuffers(1, &this->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    unsigned long vertexDataLength = vertexPositions.size();
    glBufferData(GL_ARRAY_BUFFER, vertexDataLength * sizeof(GLfloat), vertexPositions.data(), GL_STATIC_DRAW);
    
    this->bufferSize = (int)vertexDataLength;
    
    glGenBuffers(1, &this->vertexNormalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexNormalBuffer);
    unsigned long vertexNormalDataLength = objData.vertexNormalData.size();
    glBufferData(GL_ARRAY_BUFFER, vertexNormalDataLength * sizeof(GLfloat), objData.vertexNormalData.data(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &this->vertexTexCoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexTexCoordBuffer);
    unsigned long vertexTexCoordDataLength = objData.vertexTexCoordData.size();
    glBufferData(GL_ARRAY_BUFFER, vertexTexCoordDataLength * sizeof(GLfloat), objData.vertexTexCoordData.data(), GL_STATIC_DRAW);
}

void SceneObject::addTexture(string texFilePath) {
    
}

float SceneObject::intersectRay(glm::vec3 rayStartPos, glm::vec3 rayDir) const {
    bool intersected = false;
    float minT = INT_MAX;
    
    for (auto &meshTriangle : this->triangles) {
        float t = meshTriangle.intersectRay(rayStartPos, rayDir);
        
        if (t > 0.00001 && t < minT) {
            minT = t;
            intersected = true;
        }
    }
    
    if (intersected) {
        return minT;
    } else {
        return -1.f;
    }
}

void SceneObject::setShaders(const Shader& vertexShader, const Shader& fragmentShader) {
    printf("Linking program\n");
    this->shaderProgramID = glCreateProgram();
    
    GLuint vertexShaderID = vertexShader.getShaderID();
    GLuint fragmentShaderID = fragmentShader.getShaderID();
    
    glAttachShader(this->shaderProgramID, vertexShaderID);
    glAttachShader(this->shaderProgramID, fragmentShaderID);
    glLinkProgram(this->shaderProgramID);
    
    GLint result = GL_FALSE;
    int infoLogLength;
    
    // Check the program
    glGetProgramiv(this->shaderProgramID, GL_LINK_STATUS, &result);
    glGetProgramiv(this->shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    if (infoLogLength > 0) {
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(this->shaderProgramID, infoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    }
    
    glDetachShader(this->shaderProgramID, vertexShaderID);
    glDetachShader(this->shaderProgramID, fragmentShaderID);

//    glDeleteShader(vertexShaderID);
//    glDeleteShader(fragmentShaderID);
}

void SceneObject::update() {
    this->position[0] += 0.02;
    this->modelMatrix = glm::translate(glm::mat4(1.0f), this->position);
}
