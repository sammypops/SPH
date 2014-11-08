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
    double t = module->deltat;
    double ddt ,rho, d;
    findDrhodt(plist, module);
    
    for (int i = 0; i< plist.size(); i++)
    {
        ddt = plist[i]->drhodt[0];
        
        rho =plist[i]->density[0];
        
        d = rho + t*ddt;
        
        plist[i]->density[0] = plist[i]->density[0] + t*plist[i]->drhodt[0];
    }
    
}



void pressureTimeStep(std::vector<Particle*> plist, infoModule* module)
{
    for (int i = 0; i < plist.size(); i++)
    {
        plist[i]->pressure[0] = pow(module->cs,2)*(plist[i]->density[0]-module->rho0) ;
        
    }
}

/*
    Beeman's algorithm with predictor corrector
    Works to find the next position, predict the next velocity then correct the next velocity
*/
void Beemans(std::vector<Particle*> plist, infoModule* module)
{
    double t = module->deltat;
    double dr;
    
    for (int i = 0; i<plist.size(); i++)
    {
        // don't include the wall particles maybe?
        if (plist[i]->iswall == 0)
        {
            // calculate the next positions
            for (int Dim = 0; Dim < module->nDim; Dim++)
            {
                dr =plist[i]->vel[Dim]*t + (2.0/3.0)*plist[i]->accel[Dim]*pow(t, 2) - (1.0/6.0)*plist[i]->prevAccel[Dim]*pow(t, 2);
                plist[i]->dr[Dim] = plist[i]->vel[Dim]*t + (2.0/3.0)*plist[i]->accel[Dim]*pow(t, 2) - (1.0/6.0)*plist[i]->prevAccel[Dim]*pow(t, 2);
                plist[i]->position[Dim] = plist[i]->position[Dim] + plist[i]->dr[Dim];
            }
            
            // predict the next velocities
            for (int Dim = 0; Dim < module->nDim; Dim++)
            {
                plist[i]->velOld[Dim] = plist[i]->vel[Dim];
                plist[i]->vel[Dim] = plist[i]->vel[Dim] + plist[i]->vel[Dim]*t + (3.0/2.0)*plist[i]->accel[Dim]*t - (1.0/2.0)*plist[i]->prevAccel[Dim]*t;
            }
        }
        
        
        
        
        
        
        
    }
    
        // use this velocity to get new forces
    
        densityTimeStep(plist, module); // get new densities
    
        pressureTimeStep(plist,module); // get new pressures
        
        // work out the next acceleration
        findNextAccel(plist, module);
    
    
    for (int i = 0; i<plist.size(); i++)
    {
        if (plist[i]->iswall == 1) {
            continue;
        }
        //correct velocities for use in positions next time
        for (int Dim = 0; Dim < module->nDim; Dim++)
        {
            plist[i]->vel[Dim] = plist[i]->velOld[Dim] + (5.0/12.0)*plist[i]->nextAccel[Dim]*t + (2.0/3.0)*plist[i]->accel[Dim]*t - (1.0/12.0)*plist[i]->prevAccel[Dim]*t;
            // move the accelerations for the next time step
            plist[i]->prevAccel[Dim] = plist[i]->accel[Dim];
            plist[i]->accel[Dim] = plist[i]->nextAccel[Dim];
        }
        
    }
    
    
}
