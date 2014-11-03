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

void createWall(std::array<double, 3> start, std::array<double, 3> finish, double deltax);

#endif /* defined(__SPH__Initialise__) */
