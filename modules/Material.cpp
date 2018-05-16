//
//  Material.cpp
//  modules
//
//  Created by Guanlun Zhao on 5/16/18.
//  Copyright © 2018 Guanlun Zhao. All rights reserved.
//

#include "Material.hpp"

Material::Material(float diffuseColor[]) {
    this->diffuseColor = new float[3];
    this->diffuseColor[0] = diffuseColor[0];
    this->diffuseColor[1] = diffuseColor[1];
    this->diffuseColor[2] = diffuseColor[2];
}
