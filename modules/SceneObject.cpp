//
//  SceneObject.cpp
//  modules
//
//  Created by Guanlun Zhao on 11/27/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "SceneObject.hpp"
#include <iostream>
using namespace std;

SceneObject::SceneObject(const GLfloat vertexData[]) {
    glGenBuffers(1, &this->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

    cout << sizeof(vertexData) << endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}
