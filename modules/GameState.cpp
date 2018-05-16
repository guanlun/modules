//
//  GameStateManager.cpp
//  modules
//
//  Created by Guanlun Zhao on 12/23/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "GameState.hpp"

const string PROJECT_DIR = "/Users/guanlun/Workspace/modules/modules/";
const string OBJ_DIR = PROJECT_DIR + "data/";
const string SHADER_DIR = PROJECT_DIR + "shaders/";

GameState::GameState() : lightPos(glm::vec3(6, 8, 10)), mainCam(Camera(glm::vec3(10, 10, 10))) {
    Shader simpleVertexShader("vertex", SHADER_DIR + "SimpleVertexShader");
    Shader simpleFragmentShader("fragment", SHADER_DIR + "SimpleFragmentShader");
    
    SceneObject teapot(ObjectData(OBJ_DIR + "teapot.obj"), glm::vec3(2, 0, 0));
    teapot.setShaders(simpleVertexShader, simpleFragmentShader);
    this->sceneObjects.push_back(teapot);
    
    SceneObject cube(ObjectData(OBJ_DIR + "cube.obj"), glm::vec3(0, 0, -1));
    cube.setShaders(simpleVertexShader, simpleFragmentShader);
    this->sceneObjects.push_back(cube);
}
