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

using namespace std;

class SceneObject {
public:
    SceneObject(ObjectData objData);
    
    inline glm::mat4 getModelMatrix() const { return modelMatrix; };
    inline GLuint getVertexBuffer() const { return vertexBuffer; };
    inline GLuint getShaderProgramID() const { return shaderProgramID; };
    inline int getBufferSize() const { return bufferSize; };
    
    void loadShaders(const char* vertShaderPath, const char* fragShaderPath);
    
protected:
    int bufferSize;
    GLuint vertexBuffer;
    GLuint vertexNormalBuffer;
    GLuint shaderProgramID;
    
    glm::mat4 modelMatrix;
};

#endif /* SceneObject_hpp */
