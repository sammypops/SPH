//
//  Density.h
//  SPH
//
//  Created by Sam Hunter on 04/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#ifndef __SPH__Density__
#define __SPH__Density__

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include "MyStructs.h"
#include "Par.h"
#include "Kernel.h"

void findDrhodt(std::vector<Particle*> plist, infoModule* module);

#endif /* defined(__SPH__Density__) */
