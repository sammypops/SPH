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
#include "Density.h"




int main(int argc, const char * argv[])
{
    using namespace std;    // gives us access to cout and endl

    // declare variables
    
    infoModule simInfo;
    
    
    
    double rho0 = 1000.;
    double deltax = 0.05;
    double h = 1.3*deltax;
    
    int nDim = 2;
    
    array<double, 6> domain = {0.0, 2.0, 0.0, 2.0, 0.0, 0.0};
    
    
    simInfo.deltax = deltax;
    simInfo.domain = domain;
    simInfo.h = h;
    simInfo.rho0 = rho0;
    simInfo.nDim = nDim;
    
    simInfo.deltat = 0.001;
    simInfo.simTime = 0.0;
    
    
    double timed;
    
    
    std::clock_t t;
    
    
    
    // create particle list
    vector<Particle*> listofparticles;
    
    // create particles and initialise them
    cout<<"Beginning particle initialisation \n \n";
    
    createWall(&listofparticles, {-3.0*deltax,-3.0*deltax,0}, {2+3.0*deltax,-deltax,0}, &simInfo);
    createWall(&listofparticles, {-3.0*deltax,deltax,0}, {-deltax,2+3.0*deltax,0}, &simInfo);
    createWall(&listofparticles, {2 + deltax,deltax,0}, {2 + 3*deltax,2+3.0*deltax,0}, &simInfo);
    
    cout<<"Particle wall initialisation finished \n"<< listofparticles.size() <<" Particles \n \n";
    
    createFuid(&listofparticles, {0,0,0}, {1,1,0}, &simInfo);
    
    
    
    initPressure(listofparticles, &simInfo);
    
    cout<<"Particle initialisation finished \n"<< listofparticles.size() <<" Particles \n \n";
    
    
    
    // for each particle, find neighbours
    cout<<"Finding neighbours \n \n";
    t = clock();
    FNMT8(listofparticles, &simInfo);
    t = (clock() - t);
    timed = t / (double) CLOCKS_PER_SEC;
    cout<<"Neighbours found in "<< timed/8 << " seconds \n \n";
    
    
    cout<<"Updating neighbours \n \n";
    t = clock();
    updateNeighboursMT8(listofparticles, &simInfo);
    t = (clock() - t);
    timed = t / (double) CLOCKS_PER_SEC;
    cout<<"Neighbours found in "<< timed/8 << " seconds \n \n";
    
    
    // calculate drho/dt by summing over neighbours
    
    findDensity(listofparticles,&simInfo);
    
        
    findAccel(listofparticles,&simInfo);
    
    // output some stuff
    
    cout<< "particle 0's position is (" << listofparticles[0]->position[0] << "," << listofparticles[0]->position[1] << ") \n";
    
    
    for (int i = 0; i<listofparticles.size(); i++)
    {
        //cout<< "the change in density at x = " << listofparticles[i]->position[0]<< " , y = "<< listofparticles[i]->position[1]<< " is " << listofparticles[i]->drhodt[0]<< " \n";
        if (listofparticles[i]->position[0] > 0.499 && listofparticles[i]->position[0] < 0.501 && listofparticles[i]->position[1] > 0.499 && listofparticles[i]->position[1]< 0.501)
        {
            cout<< "the pressure at "<< i << " " << listofparticles[i]->position[0] << " " << listofparticles[i]->position[1] <<" is " << listofparticles[i]->pressure[0] << ") \n";
        }
        
    }
    
    
    cout << "Hello, World!\n";
    return 0;
}
