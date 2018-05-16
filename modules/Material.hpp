//
//  Material.hpp
//  modules
//
//  Created by Guanlun Zhao on 5/16/18.
//  Copyright © 2018 Guanlun Zhao. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <iostream>
using namespace std;

class Material {
public:
    Material(float diffuseColor[]);
    float* diffuseColor;
};

#endif /* Material_hpp */
