//
//  Kernel.cpp
//  SPH
//
//  Created by Sam Hunter on 30/10/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "Kernel.h"


double wendkernel(double r, infoModule* module)
{
    double k = 0.0;
    double q = fabs(r/module->h);
    double pi = 3.14159;
    
    k = (7/(4*pi*pow(module->h,2)))*(5.0/8.0)*pow((q-2),3)*q;
    
    if (r<0) {
        k = -1*k;
    }
    
    
    return k;
}

double gausskernel(double r, infoModule* module)
{
    double k = 0.0;
    double pi = 3.14159;
    double q = r/module->h;
    
    k = 1/(pi*pow(module->h,2))*-2*q*exp(-1*pow(q, 2));
    
    return k;
}

double quadkernel(double r, infoModule* module)
{
    double k = 0.0;
    
    k = (-3/(8*module->h*module->h))*(2-fabs(r)/module->h);
    
    if (r<0) {
        k = -1*k;
    }
    
    
    return k;
}

