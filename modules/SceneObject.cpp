//
//  SceneObject.cpp
//  modules
//
//  Created by Guanlun Zhao on 11/27/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "SceneObject.hpp"

SceneObject::SceneObject(ObjectData objData, glm::vec3 pos) {
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
//
//    glDeleteShader(vertexShaderID);
//    glDeleteShader(fragmentShaderID);
}

void SceneObject::loadShaders(string vertShaderPath, string fragShaderPath) {
    // Create the shaders
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertShaderPath, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    } else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertShaderPath.c_str());
        getchar();
        return;
    }
    
    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragShaderPath, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }
    
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    
    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertShaderPath.c_str());
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(vertexShaderID);
    
    // Check Vertex Shader
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }
    
    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragShaderPath.c_str());
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(fragmentShaderID);
    
    // Check Fragment Shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(fragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }
    
    
    
    // Link the program
    printf("Linking program\n");
    this->shaderProgramID = glCreateProgram();
    glAttachShader(this->shaderProgramID, vertexShaderID);
    glAttachShader(this->shaderProgramID, fragmentShaderID);
    glLinkProgram(this->shaderProgramID);
    
    // Check the program
    glGetProgramiv(this->shaderProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(this->shaderProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(this->shaderProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
    
    
    glDetachShader(this->shaderProgramID, vertexShaderID);
    glDetachShader(this->shaderProgramID, fragmentShaderID);
    
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    
//    return ProgramID;
}
