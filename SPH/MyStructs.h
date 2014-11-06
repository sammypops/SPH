//
//  MyStructs.h
//  SPH
//
//  Created by Sam Hunter on 03/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#ifndef __SPH__MyStructs__
#define __SPH__MyStructs__

#include <iostream>
#include <array>

struct infoModule{
    
    std::array<double, 6> domain;
    double deltax;
    double h;
    double rho0;
    double x;
    double y;
    
    double simTime;
    double finishTime;
    double deltat;
    double outputTime;
    
    int nDim;
    int nWallPar;
    int fileN;
    int iterationN;
    int finishIteration;
    int outputIteration;
    
};

#endif /* defined(__SPH__MyStructs__) */
