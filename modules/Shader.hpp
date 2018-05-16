//
//  Shader.hpp
//  modules
//
//  Created by Guanlun Zhao on 5/16/18.
//  Copyright © 2018 Guanlun Zhao. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace std;

class Shader {
public:
    Shader(string shaderType, string shaderPath);
    
    inline GLuint getShaderID() const { return shaderID; };
private:
    GLuint shaderID;
};

#endif /* Shader_hpp */
