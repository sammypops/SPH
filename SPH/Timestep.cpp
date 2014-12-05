//
//  Timestep.cpp
//  SPH
//
//  Created by Sam Hunter on 05/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "Timestep.h"

void variableTimeStep(std::vector<Particle*> plist, infoModule* module)
{
    int refreshCounter = 0;
    
    
    
    for (module->iterationN = 0; module->iterationN < module->finishIteration; module->iterationN++)
    {
        
        if (module->timeCounter > module->outputTime)
        {
            writeParticles(plist, module);
            module->fileN++;
            module->timeCounter = module->timeCounter - module->outputTime;
        }
        
        Beemans(plist, module);
        
        //cout << module->simTime << " P = " << plist[246]->pressure[0] << " Neighbours = " << plist[246]->neighbours.size() << endl;
        
        if (refreshCounter >= module->neighbourRefresh )
        {
            refreshCounter = 0;
            FNMT8(plist, module);
        }
        else
        {
            updateNeighboursMT8(plist, module);
        }
        
        
        module->simTime = module->simTime + module->deltat;
        
    }
    
    
}

void constTimeStep(std::vector<Particle*> plist, infoModule* module)
{
    std::vector<Particle*> flist;
    
    for (int i = module->nWallPar; i < plist.size(); i++)
    {
        flist.push_back(plist[i]);
    }
    
    int refreshCounter = 0;
    
    for (module->iterationN = 0; module->iterationN < module->finishIteration; module->iterationN++)
    {
        
        if (module->iterationN == 0 || module->iterationN % module->outputIteration == 0 )
        {
            //writeParticles(plist, module);
            writeFluid(plist, module);
            module->fileN++;
        }
        
        Beemans(flist, module);
        
        if (refreshCounter >= module->neighbourRefresh )
        {
            cout << "refreshing neighbour list"<< endl;
            refreshCounter = 0;
            FNMT8(plist, module);
        }
        else
        {
            updateNeighboursMT8(plist, module);
            refreshCounter++;
        }
        
        module->simTime = module->simTime + module->deltat;
        
        cout << "iteration #"<< module->iterationN << endl;
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
        // don't include the wall particles
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
    
    
        DTSMT8(plist, module); // get new densities
    
        PTSMT8(plist,module); // get new pressures
     
   
    
    
        // work out the next acceleration
        //findNextAccel(plist, module);
        FNAMT8(plist, module);
    
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
