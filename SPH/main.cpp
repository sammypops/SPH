//
//  main.cpp
//  SPH
//
//  Created by Sam Hunter on 24/10/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include "Par.h"
#include "Initialise.h"
#include "NNA.h"
#include "Kernel.h"
#include "Momentum.h"
#include "MyStructs.h"
#include "Initialise.h"
#include "WallSetUp.h"
#include "Density.h"
#include "Timestep.h"
#include "output.h"




int main(int argc, const char * argv[])
{
    using namespace std;    // gives us access to cout and endl

    // declare variables
    
    infoModule simInfo;
    
    
    
    double rho0 = 1000.;
    double deltax = 0.1;
    double h = 1.3*deltax;
    
    int nDim = 3;
    
    array<double, 6> domain = {0.0, 2.0, 0.0, 2.0, 0.0, 0.0};
    
    
    simInfo.deltax = deltax;
    simInfo.domain = domain;
    simInfo.h = h;
    simInfo.rho0 = rho0;
    simInfo.nDim = nDim;
    
    simInfo.cs = 10*sqrt(9.81*1);
    
    simInfo.deltat = 0.1*simInfo.h/simInfo.cs;
    cout <<" delta t = " << simInfo.deltat << endl;
    
    simInfo.simTime = 0.0;
    simInfo.timeCounter = 0.0;
    
    simInfo.finishTime = 16.00;
    simInfo.outputTime = 0.016;
    
    simInfo.fileN = 0;
    simInfo.iterationN = 0;
    simInfo.neighbourRefresh = 10;
    
    simInfo.finishIteration = int(floor(simInfo.finishTime/simInfo.deltat));
    
    simInfo.outputIteration = int(floor(simInfo.outputTime/simInfo.deltat));
    
    
    
    double timed;
    
    
    std::clock_t t;
    
    
    
    // create particle list
    vector<Particle*> listofparticles;
    
    // create particles and initialise them
    cout<<"Beginning particle initialisation \n \n";
    
    box3DOpen(&listofparticles, &simInfo);
    
    simInfo.nWallPar = int(listofparticles.size());
    
    cout<<"Particle wall initialisation finished \n"<< listofparticles.size() <<" Particles \n \n";
    
    createFuid(&listofparticles, {0.05,0.05,0.05}, {1,1,1}, &simInfo);
    
    
    
    initPressure2(listofparticles, &simInfo);
    
    cout<<"Particle initialisation finished \n"<< listofparticles.size() <<" Particles \n \n";
    
    
    
    // for each particle, find neighbours
    cout<<"Finding neighbours \n \n";
    t = clock();
    FNMT8(listofparticles, &simInfo);
    t = (clock() - t);
    timed = t / (double) CLOCKS_PER_SEC;
    cout<<"Neighbours found in "<< timed/8 << " seconds \n \n";
    
    initWallPressure(listofparticles, &simInfo);
    
    cout<<"Updating neighbours \n \n";
    t = clock();
    updateNeighboursMT8(listofparticles, &simInfo);
    t = (clock() - t);
    timed = t / (double) CLOCKS_PER_SEC;
    cout<<"Neighbours found in "<< timed/8 << " seconds \n \n";
    
    findAccel(listofparticles,&simInfo);
    
    
    
    
    constTimeStep(listofparticles, &simInfo);
    
    
    
    
    
    // output some stuff
    
    
    
    for (int i = 0; i<listofparticles.size(); i++)
    {
        //cout<< "the change in density at x = " << listofparticles[i]->position[0]<< " , y = "<< listofparticles[i]->position[1]<< " is " << listofparticles[i]->drhodt[0]<< " \n";
        if (listofparticles[i]->position[0] > 0.495 && listofparticles[i]->position[0] < 0.505 && listofparticles[i]->position[1] > 0.495 && listofparticles[i]->position[1]< 0.505)
        {
            cout<< "the pressure at "<< i << " " << listofparticles[i]->position[0] << " " << listofparticles[i]->position[1] <<" is " << listofparticles[i]->pressure[0] << ") \n";
        }
        
    }
    
    
    cout << "Hello, World!\n";
    return 0;
}
