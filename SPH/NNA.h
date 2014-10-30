//
//  NNA.h
//  SPH
//
//  Created by Sam Hunter on 30/10/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#ifndef SPH_NNA_h
#define SPH_NNA_h

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <stdlib.h>
#include "Par.h"

using namespace std;

void findNeighboursMT4(std::vector<Particle*> plist, double h);
void findNeighboursMT8(std::vector<Particle*> plist, double h);
void multiThreadNeighbour(void (*the_function)(std::vector<Particle*>, double), std::vector<Particle*> plist, double h, int nthreads);
void findNeighbours(std::vector<Particle*> plist, double h);
void updateNeighboursMT8(std::vector<Particle*> plist, double h);
void updateNeighbours (std::vector<Particle*> plist, double h);

#endif
