//
//  Timestep.cpp
//  SPH
//
//  Created by Sam Hunter on 05/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "Timestep.h"

void densityTimeStep(std::vector<Particle*> plist, infoModule* module)
{
    double k1,k2,k3,k4;
    double t = module->deltat;
    
    
}
/*
    Beeman's algorithm with predictor corrector
    Works to find the next position, predict the next velocity then correct the next velocity
*/
void Beemans(std::vector<Particle*> plist, infoModule* module)
{
    double t = module->deltat;
    
    for (int i = 0; i<plist.size(); i++)
    {
        // don't include the wall particles maybe?
        if (plist[i]->iswall == 1) {
            continue;
        }
        
        // calculate the next positions
        for (int Dim = 0; Dim < module->nDim; Dim++)
        {
            plist[i]->position[Dim] = plist[i]->position[Dim] + plist[i]->vel[Dim]*t + (2.0/3.0)*plist[i]->accel[Dim]*pow(t, 2) - (1.0/6.0)*plist[i]->prevAccel[Dim]*pow(t, 2);
        }
        // predict the next velocities
        for (int Dim = 0; Dim < module->nDim; Dim++)
        {
            plist[i]->vel[Dim] = plist[i]->vel[Dim] + plist[i]->vel[Dim]*t + (3.0/2.0)*plist[i]->accel[Dim]*t - (1.0/2.0)*plist[i]->prevAccel[Dim]*t;
        }
    }
    
        // use this velocity to get new forces
        
        
        // work out the next acceleration
        findNextAccel(plist, module);
    
    
    for (int i = 0; i<plist.size(); i++)
    {
        //correct velocities for use in positions next time
        for (int Dim = 0; Dim < module->nDim; Dim++)
        {
            plist[i]->vel[Dim] = plist[i]->vel[Dim] + (5.0/12.0)*plist[i]->nextAccel[Dim]*t + (2.0/3.0)*plist[i]->accel[Dim]*t - (1.0/12.0)*plist[i]->prevAccel[Dim]*t;
            // move the accelerations for the next time step
            plist[i]->prevAccel[Dim] = plist[i]->accel[Dim];
            plist[i]->accel[Dim] = plist[i]->nextAccel[Dim];
        }
        
    }
    
    
}