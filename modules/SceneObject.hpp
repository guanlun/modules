//
//  SceneObject.hpp
//  modules
//
//  Created by Guanlun Zhao on 11/27/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <vector>

#include "ObjectData.hpp"
#include "MeshTriangle.hpp"
#include "Shader.hpp"

using namespace std;

class SceneObject {
public:
    SceneObject(ObjectData objData, glm::vec3 pos);
    
    inline glm::mat4 getModelMatrix() const { return modelMatrix; };
    inline GLuint getVertexBuffer() const { return vertexBuffer; };
    inline GLuint getVertexNormalBuffer() const { return vertexNormalBuffer; };
    inline GLuint getVertexTexCoordBuffer() const { return vertexTexCoordBuffer; };
    inline GLuint getShaderProgramID() const { return shaderProgramID; };
    inline int getBufferSize() const { return bufferSize; };
    
    float intersectRay(glm::vec3 rayStartPos, glm::vec3 rayDir) const;
    void addTexture(string texFilePath);
    void loadShaders(string vertShaderPath, string fragShaderPath);
    void setShaders(const Shader& vertexShader, const Shader& fragmentShader);
    
protected:
    int bufferSize;
    GLuint vertexBuffer;
    GLuint vertexNormalBuffer;
    GLuint vertexTexCoordBuffer;
    GLuint shaderProgramID;
    
    glm::mat4 modelMatrix;
    
    vector<MeshTriangle> triangles;
};

#endif /* SceneObject_hpp */
