//
//  ObjectLoader.hpp
//  modules
//
//  Created by Guanlun Zhao on 12/1/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#ifndef ObjectLoader_hpp
#define ObjectLoader_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class ObjectLoader {
public:
    static vector<GLfloat> readObjectFile(const char* filename);
};

#endif /* ObjectLoader_hpp */
