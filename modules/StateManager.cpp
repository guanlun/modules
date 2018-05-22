//
//  StateManager.cpp
//  modules
//
//  Created by Guanlun Zhao on 5/16/18.
//  Copyright © 2018 Guanlun Zhao. All rights reserved.
//

#include "StateManager.hpp"

void StateManager::updateState(GameState *currGameState) {
    for (auto iter = currGameState->sceneObjects.begin(); iter != currGameState->sceneObjects.end(); iter++) {
        SceneObject& obj = *iter;
        obj.update();
    }
}
