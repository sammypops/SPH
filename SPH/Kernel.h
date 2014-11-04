//
//  Kernel.h
//  SPH
//
//  Created by Sam Hunter on 30/10/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#ifndef __SPH__Kernel__
#define __SPH__Kernel__

#include <iostream>
#include <cmath>
#include "MyStructs.h"

double wendkernel(double r, infoModule* module);
double gausskernel(double r, infoModule* module);
double quadkernel(double r, infoModule* module);

#endif /* defined(__SPH__Kernel__) */
