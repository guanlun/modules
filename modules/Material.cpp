//
//  Material.cpp
//  modules
//
//  Created by Guanlun Zhao on 5/16/18.
//  Copyright © 2018 Guanlun Zhao. All rights reserved.
//

#include "Material.hpp"

Material::Material(float diffuseColor[], float specularColor[]) {
    this->diffuseColor = new float[3];
    this->diffuseColor[0] = diffuseColor[0];
    this->diffuseColor[1] = diffuseColor[1];
    this->diffuseColor[2] = diffuseColor[2];
    
    this->specularColor = new float[3];
    this->specularColor[0] = specularColor[0];
    this->specularColor[1] = specularColor[1];
    this->specularColor[2] = specularColor[2];
}
