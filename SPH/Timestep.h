//
//  Timestep.h
//  SPH
//
//  Created by Sam Hunter on 05/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#ifndef __SPH__Timestep__
#define __SPH__Timestep__

#include <iostream>
#include <cmath>
#include <vector>
#include "Par.h"
#include "MyStructs.h"
#include "Momentum.h"
#include "Density.h"
#include "NNA.h"
#include "output.h"

void Beemans(std::vector<Particle*> plist, infoModule* module);


void constTimeStep(std::vector<Particle*> plist, infoModule* module);
void variableTimeStep(std::vector<Particle*> plist, infoModule* module);


#endif /* defined(__SPH__Timestep__) */
