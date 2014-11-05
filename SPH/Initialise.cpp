//
//  Initialise.cpp
//  SPH
//
//  Created by Sam Hunter on 03/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "Initialise.h"

/*
    creates a box, square or line of wall particles, be careful not to put wall particles on top of fluids and vice versa
 */

void createWall(std::vector<Particle*>* plist, std::array<double, 3> start, std::array<double, 3> finish, infoModule* module)
{
    for (double i = start[0]; i <= finish[0]; i = i + module->deltax)
    {
        for (double j = start[1]; j<= finish[1]; j = j + module->deltax)
        {
            for (double k = start[2]; k<= finish[2]; k = k + module->deltax)
            {
                //******************************************************************************************
                plist->push_back(new Particle(1, {i,j}, {module->rho0*module->deltax, 0.0 , module->rho0})); // uses the wall constructor
                //******************************************************************************************
            }
            
        }
        
    }
    
}
/*
    creates a box or square of particles given the opposite corners of the shape.
 */


void createFuid(std::vector<Particle*>* plist, std::array<double, 3> start, std::array<double, 3> finish, infoModule* module)
{
    for (double i = start[0]; i <= finish[0]+0.00001; i = i + module->deltax)
    {
        for (double j = start[1]; j<= finish[1]+0.00001; j = j + module->deltax)
        {
            for (double k = start[2]; k<= finish[2]+0.00001; k = k + module->deltax)
            {
                //**************************************************************************************************
                plist->push_back(new Particle({i,j}, {0.0,0.0}, {module->rho0*module->deltax, 0.0, module->rho0}));
                //**************************************************************************************************
            }
            
        }
        
    }
    
}

/* 
 bit of a hack way of initialising pressure.
 find a line of vertical particles and give them a pressure gradient which
 is dependant on the top and bottom particle.
 Only works for cube shaped latices of particles
 
 future work?:  work over a range of x values in the domain
                or move to 3D code finding vertical strings
                of particles in the Z direction.
*/
void initPressure(std::vector<Particle*> plist, infoModule* module)
{
    std::vector<Particle*> sub, remaining;
    int i = 1;
    
    double bigY, smallY, yDiff;
    
    sub.push_back(plist[0]);
    bigY = sub[0]->position[1];
    smallY = sub[0]->position[1];
    remaining = plist;
    
    while (remaining.size()>0)
    {
        if (i>=remaining.size())
        {
            i = 0;
            
            yDiff = bigY - smallY;
            
            for (int n = 0; n< sub.size(); n++)
            {
                
                if (sub[n]->position[0] > 0.499 && sub[n]->position[0] < 0.501 && sub[n]->position[1] > 0.499 && sub[n]->position[1]< 0.501)
                {
                    cout<< "the pressure at "<< i << " " << sub[n]->position[0] << " " << sub[n]->position[1] <<" is " << sub[n]->pressure[0] << ") \n";
                }
                
                sub[n]->pressure[0] = module->rho0 * 9.81 * (bigY - sub[n]->position[1]);
            }
            
            
            sub.clear();
            sub.push_back(remaining[0]);
            continue;
            
        }
        if (remaining[i]->iswall == 1)
        {
            remaining.erase(remaining.begin()+i);
            continue;
        }
        if (sub[0]->position[0] == remaining[i]->position[0] )
        {
            sub.push_back(remaining[i]);
            if (remaining[i]->position[1] > bigY)
            {
                bigY = remaining[i]->position[1];
            }
            else if (remaining[i]->position[1] < smallY)
            {
                smallY = remaining[i]->position[1] ;
            }
            remaining.erase(remaining.begin()+i);
            continue;
        }
        i++;
    }
    
    
    
    
}









