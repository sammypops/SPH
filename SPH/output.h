//
//  output.h
//  SPH
//
//  Created by Sam Hunter on 06/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#ifndef __SPH__output__
#define __SPH__output__

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Par.h"
#include "MyStructs.h"

using namespace std;

void writeParticles(std::vector<Particle*> plist, infoModule* module);
void writeFluid(std::vector<Particle*> plist, infoModule* module);

#endif /* defined(__SPH__output__) */
