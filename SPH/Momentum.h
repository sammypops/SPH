//
//  Momentum.h
//  SPH
//
//  Created by Sam Hunter on 03/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#ifndef __SPH__Momentum__
#define __SPH__Momentum__

#include <iostream>
#include <cmath>
#include <vector>
#include "Par.h"
#include "Kernel.h"

void momentum(std::vector<Particle*> plist, infoModule* module);

#endif /* defined(__SPH__Momentum__) */
