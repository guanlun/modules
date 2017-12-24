//
//  GameStateManager.cpp
//  modules
//
//  Created by Guanlun Zhao on 12/23/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "GameState.hpp"

GameState::GameState() : lightPos(glm::vec3(6, 8, 10)), mainCam(Camera(glm::vec3(10, 10, 10))) {
    SceneObject teapot(ObjectData("/Users/guanlun/Workspace/modules/modules/data/teapot.obj"), glm::vec3(2, 0, 0));
    teapot.loadShaders("/Users/guanlun/Workspace/modules/modules/SimpleVertexShader.vertexshader", "/Users/guanlun/Workspace/modules/modules/SimpleFragmentShader.fragmentshader");
    this->sceneObjects.push_back(teapot);
    
    SceneObject cube(ObjectData("/Users/guanlun/Workspace/modules/modules/data/cube.obj"), glm::vec3(0, 0, -1));
    cube.loadShaders("/Users/guanlun/Workspace/modules/modules/SimpleVertexShader.vertexshader", "/Users/guanlun/Workspace/modules/modules/SimpleFragmentShader.fragmentshader");
    this->sceneObjects.push_back(cube);
}
