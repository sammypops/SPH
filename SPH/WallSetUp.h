//
//  WallSetUp.h
//  SPH
//
//  Created by Sam Hunter on 10/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#ifndef __SPH__WallSetUp__
#define __SPH__WallSetUp__

#include <iostream>
#include <cmath>
#include <array>
#include <vector>

#include "Par.h"
#include "MyStructs.h"
#include "Initialise.h"


void box3DOpen(std::vector<Particle*>* plist, infoModule* module);
void box2DOpen(std::vector<Particle*>* plist, infoModule* module);


#endif /* defined(__SPH__WallSetUp__) */
