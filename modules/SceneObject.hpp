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

using namespace std;

class SceneObject {
public:
    SceneObject(const GLfloat vertexData[], int vertexDataSize);
    
    inline glm::mat4 getModelMatrix() const { return modelMatrix; };
    inline GLuint getVertexBuffer() const { return vertexBuffer; };
    inline GLuint getShaderProgramID() const { return shaderProgramID; };
    
    void loadShaders(const char* vertShaderPath, const char* fragShaderPath);
    
protected:
    GLuint vertexBuffer;
    GLuint shaderProgramID;
    
    glm::mat4 modelMatrix;
};

#endif /* SceneObject_hpp */
