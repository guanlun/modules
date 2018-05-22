//
//  StateManager.hpp
//  modules
//
//  Created by Guanlun Zhao on 5/16/18.
//  Copyright © 2018 Guanlun Zhao. All rights reserved.
//

#ifndef StateManager_hpp
#define StateManager_hpp

#include "GameState.hpp"

class StateManager {
public:
    static void updateState(GameState* currGameState);
};

#endif /* StateManager_hpp */
