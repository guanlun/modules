//
//  Renderer.hpp
//  modules
//
//  Created by Guanlun Zhao on 12/23/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include "GameState.hpp"
#include "StateManager.hpp"
#include "Camera.hpp"
#include "SceneRenderer.hpp"

#include <GLFW/glfw3.h>

class Application {
public:
    Application();
    
    bool initWindow();
    
    void start();
private:
    GLFWwindow* window;
    
    SceneRenderer* sceneRenderer;
    GameState* gameState;
};

#endif /* Renderer_hpp */
