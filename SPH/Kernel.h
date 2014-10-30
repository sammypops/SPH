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

double wendkernel(double r, double h);
double gausskernel(double r, double h);
double quadkernel(double r, double h);

#endif /* defined(__SPH__Kernel__) */
