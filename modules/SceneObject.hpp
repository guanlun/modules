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

class SceneObject {
public:
    SceneObject(const GLfloat vertexData[]);
    
    inline GLuint getVertexBuffer() const { return vertexBuffer; };
protected:
    GLuint vertexBuffer;
};

#endif /* SceneObject_hpp */
