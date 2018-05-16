//
//  Shader.cpp
//  modules
//
//  Created by Guanlun Zhao on 5/16/18.
//  Copyright © 2018 Guanlun Zhao. All rights reserved.
//

#include <fstream>
#include <vector>
#include "Shader.hpp"

Shader::Shader(string shaderType, string shaderPath) {
    this->shaderID = glCreateShader(shaderType == "vertex" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    
    std::string shaderCode;
    std::ifstream shaderInputStream(shaderPath, std::ios::in);
    if(shaderInputStream.is_open()){
        std::string Line = "";
        while(getline(shaderInputStream, Line))
            shaderCode += "\n" + Line;
        shaderInputStream.close();
    } else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", shaderPath.c_str());
        getchar();
        return;
    }
    
    GLint result = GL_FALSE;
    int infoLogLength;
    
    // Compile Shader
    printf("Compiling shader : %s\n", shaderPath.c_str());
    char const * sourcePointer = shaderCode.c_str();
    glShaderSource(this->shaderID, 1, &sourcePointer , NULL);
    glCompileShader(this->shaderID);
    
    // Check Shader
    glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(this->shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> shaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(this->shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
        printf("%s\n", &shaderErrorMessage[0]);
    }
}
