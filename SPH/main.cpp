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
#include "NNA.h"
#include "Kernel.h"

double somekernel(double r);



int main(int argc, const char * argv[])
{
    using namespace std;    // gives us access to cout and endl

    // declare variables
    double rho0 = 1000.;
    double r = 0.0;
    double deltax = 0.2;
    double h = 1.3*deltax;
    double dkernel = 0.0;
    double sum = 0.0;
    double xr = 0.0;
    double x = 10.0;
    double y = 10.01;
    double timed;
    
    
    std::clock_t t;
    
    // create particle list
    vector<Particle*> listofparticles;
    
    // create particles and initialise them
    cout<<"Beginning particle initialisation \n \n";
    for (double i = 0; i < x; i = i + deltax)
    {
        for (double j=0; j<y; j = j+ deltax)
        {
            listofparticles.push_back(new Particle({i,j, 10*i,0.0,rho0*deltax}));
            // particles have vel {10x,0} and mass rho0*deltax
        }
        
    }
    cout<<"Particle initialisation finished \n"<< listofparticles.size() <<" Particles \n \n";
    
    // for each particle, find neighbours
    cout<<"Finding neighbours \n \n";
    
    t = clock();
    //findNeighboursMT8(listofparticles, h);
    multiThreadNeighbour(&findNeighbours, listofparticles, h, 8);
    t = (clock() - t);
    timed = t / (double) CLOCKS_PER_SEC;
    
    cout<<"Neighbours found in "<< timed/8 << " seconds \n \n";
    
    cout<<"Updating neighbours \n \n";
    t = clock();
    //multiThreadNeighbour(&updateNeighbours, listofparticles, h, 8);
    t = (clock() - t);
    timed = t / (double) CLOCKS_PER_SEC;
    cout<<"Neighbours found in "<< timed/8 << " seconds \n \n";
    
    // calculate drho/dt by summing over neighbours
    
    for (int n = 0; n<listofparticles.size(); n++)
    {
        sum = 0.0;
        
        for (int m=0; m<listofparticles[n]->neighbours.size(); m++)
        {
            r = listofparticles[n]->neighboursdist[m];
            if (r == 0)
            {
                continue;
            }
            xr = (listofparticles[n]->position[0] - listofparticles[n]->neighbours[m]-> position[0])/r;
            dkernel = wendkernel(r,h);
            //dkernel = quadkernel(r,h);
            //dkernel = gausskernel(r,h);
            sum = sum + (listofparticles[n]->vel[0] - listofparticles[n]->neighbours[m]->vel[0])*xr*dkernel*listofparticles[n]->neighbours[m]->m[0];
        }
        // write dp/dt after summing over all of the particles
        listofparticles[n]->drhodt[0] = sum;
    }
    
    
    
    // output some stuff
    
    cout<< "particle 0's position is (" << listofparticles[0]->position[0] << "," << listofparticles[0]->position[1] << ") \n";
    
    
    for (int i = 0; i<listofparticles.size(); i++)
    {
        //cout<< "the change in density at x = " << listofparticles[i]->position[0]<< " , y = "<< listofparticles[i]->position[1]<< " is " << listofparticles[i]->drhodt[0]<< " \n";
    }
    
    
    cout << "Hello, World!\n";
    return 0;
}
