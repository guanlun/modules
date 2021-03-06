//
//  GameStateManager.hpp
//  modules
//
//  Created by Guanlun Zhao on 12/23/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#ifndef GameState_hpp
#define GameState_hpp

#include "ObjectGroup.hpp"
#include "SceneObject.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class GameState {
public:
    GameState();
    const vector<SceneObject>& getSceneObjects() const { return this->sceneObjects; };

    vector<SceneObject> sceneObjects;
    glm::vec3 lightPos;
    Camera mainCam;
};

#endif /* GameStateManager_hpp */
