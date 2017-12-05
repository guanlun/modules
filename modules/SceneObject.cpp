//
//  SceneObject.cpp
//  modules
//
//  Created by Guanlun Zhao on 11/27/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "SceneObject.hpp"


SceneObject::SceneObject(vector<GLfloat> vertexData) {
    glGenBuffers(1, &this->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    
    unsigned long vertexDataLength = vertexData.size();

    glBufferData(GL_ARRAY_BUFFER, vertexDataLength * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);
    
    this->bufferSize = (int)vertexDataLength;
    this->modelMatrix = glm::mat4(1.0f);
}

void SceneObject::loadShaders(const char* vertShaderPath, const char* fragShaderPath) {
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
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertShaderPath);
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
    printf("Compiling shader : %s\n", vertShaderPath);
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
    printf("Compiling shader : %s\n", fragShaderPath);
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
