//
//  Initialise.h
//  SPH
//
//  Created by Sam Hunter on 03/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#ifndef __SPH__Initialise__
#define __SPH__Initialise__

#include <iostream>
#include <cmath>
#include <array>
#include <vector>

#include "Par.h"  
#include "MyStructs.h"

using namespace std;

void createWall(std::vector<Particle*>* plist, std::array<double, 3> start, std::array<double, 3> finish, infoModule* module);
void createFuid(std::vector<Particle*>* plist, std::array<double, 3> start, std::array<double, 3> finish, infoModule* module);
void createLine2D(std::vector<Particle*>* plist, std::array<double, 2> len, int dim, double line, infoModule* module);
void initPressure(std::vector<Particle*> plist, infoModule* module);
void initWallPressure(std::vector<Particle*> plist, infoModule* module);



#endif /* defined(__SPH__Initialise__) */
