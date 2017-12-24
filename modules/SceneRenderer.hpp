//
//  Renderer.hpp
//  modules
//
//  Created by Guanlun Zhao on 12/23/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#ifndef SceneRenderer_hpp
#define SceneRenderer_hpp

#include "GameState.hpp"
#include <GL/glew.h>

class SceneRenderer {
public:
    SceneRenderer();
    void render(const GameState* currGameState);
private:
    
};

#endif /* Renderer_hpp */
