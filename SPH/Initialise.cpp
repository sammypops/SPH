//
//  Initialise.cpp
//  SPH
//
//  Created by Sam Hunter on 03/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "Initialise.h"

void createWall(std::vector<Particle*>* plist, std::array<double, 3> start, std::array<double, 3> finish, infoModule* module)
{
    for (double i = start[0]; i <= finish[0]; i = i + module->deltax)
    {
        for (double j = start[1]; j<= finish[1]; j = j + module->deltax)
        {
            for (double k = start[2]; k<= finish[2]; k = k + module->deltax)
            {
                //******************************************************************************************
                plist->push_back(new Particle(1, {i,j}, {module->rho0*module->deltax, 0.0 , module->rho0}));
                //******************************************************************************************
            }
            
        }
        
    }
    
}

void createFuid(std::vector<Particle*>* plist, std::array<double, 3> start, std::array<double, 3> finish, infoModule* module)
{
    for (double i = start[0]; i <= finish[0]; i = i + module->deltax)
    {
        for (double j = start[1]; j<= finish[1]; j = j + module->deltax)
        {
            for (double k = start[2]; k<= finish[2]; k = k + module->deltax)
            {
                //**************************************************************************************************
                plist->push_back(new Particle({i,j}, {0.0,0.0}, {module->rho0*module->deltax, 0.0 , module->rho0}));
                //**************************************************************************************************
            }
            
        }
        
    }
    
}

void initPressure(std::vector<Particle*> plist, infoModule* module)
{
    std::vector<Particle*> sub, remaining;
    int i = 1;
    int j = 0;
    
    sub[0] = plist[0];
    remaining = plist;
    
    while (remaining.size()>0)
    {
        if (i<=remaining.size())
        {
            i = 0;
            
            
        }
        if (sub[0]->position[0] == remaining[i]->position[0] )
        {
            sub.push_back(remaining[i]);
            remaining.erase(remaining.begin()+i);
            continue;
        }
        i++;
    }
    
    
    
    
}









