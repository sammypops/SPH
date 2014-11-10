//
//  WallSetUp.cpp
//  SPH
//
//  Created by Sam Hunter on 10/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "WallSetUp.h"

void box3DOpen(std::vector<Particle*>* plist, infoModule* module)
{
    double deltax = module->deltax;
    
    
    createWall(plist, {-deltax,-deltax,-2*deltax}, {2+deltax,2+deltax,-deltax}, module); // base
    createWall(plist, {-2*deltax,-deltax,-2*deltax}, {-deltax,2+deltax,2}, module); //wall1
    createWall(plist, {-deltax,2,-2*deltax}, {2+deltax,2+deltax,2}, module); //wall2
    createWall(plist, {2+deltax,-deltax,-2*deltax}, {2+2*deltax,2,2}, module); //wall3
    createWall(plist, {-deltax,-2*deltax,-2*deltax}, {2+deltax,-deltax,2}, module); //wall 4

}

void box2DOpen(std::vector<Particle*>* plist, infoModule* module)
{
    double deltax = module->deltax;
    
    createWall(plist, {-2*deltax,-2*deltax,0}, {2+2*deltax,-deltax,0}, module);//base
    createWall(plist, {-2*deltax,0,0}, {-deltax,2,0}, module);// left wall
    createWall(plist, {2+deltax,0,0}, {2+2*deltax,2,0}, module);// right wall
    
}