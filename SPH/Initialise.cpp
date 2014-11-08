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
                plist->push_back(new Particle(1, {i,j,k}, {module->rho0*module->deltax, 0.0 , module->rho0})); // uses the wall constructor
                //******************************************************************************************
            }
            
        }
        
    }
    
}

void createLine2D(std::vector<Particle*>* plist, std::array<double, 2> len, int dim, double line, infoModule* module)
{
    for (double i = len[0]; i <= len[1]; i = i+ module->deltax/10)
    {
        if (dim == 0)
        {
            //******************************************************************************************
            plist->push_back(new Particle(1, {line,i}, {module->rho0*module->deltax/10, 0.0 , module->rho0})); // uses the wall constructor
            //******************************************************************************************
        }
        else if (dim == 1)
        {
            //******************************************************************************************
            plist->push_back(new Particle(1, {i,line}, {module->rho0*module->deltax/10, 0.0 , module->rho0})); // uses the wall constructor
            //******************************************************************************************
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
                plist->push_back(new Particle({i,j,k}, {0.0,0.0,0.0}, {module->rho0*module->deltax, 0.0, module->rho0}));
                //**************************************************************************************************
            }
            
        }
        
    }
    
}

void initPressure2(std::vector<Particle*> plist, infoModule* module)
{
    double tallest;
    
    tallest = plist[module->nWallPar]->position[module->nDim];
    
    for (int i = module->nWallPar; i < plist.size(); i++)
    {
        if (tallest < plist[i]->position[module->nDim])
        {
            tallest = plist[i]->position[module->nDim];
        }
    }
    for (int i = module->nWallPar; i < plist.size(); i++)
    {
        plist[i]->pressure[0] =  module->rho0 * 9.81 * (tallest - plist[i]->position[module->nDim]);
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
                
                sub[n]->pressure[0] =  module->rho0 * 9.81 * (bigY - sub[n]->position[1]);
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
            
            if (remaining.size() == 0)
            {
                i = 0;
                
                yDiff = bigY - smallY;
                
                for (int n = 0; n< sub.size(); n++)
                {
                    
                    sub[n]->pressure[0] =  module->rho0 * 9.81 * (bigY - sub[n]->position[1]);
                }
                
                
                sub.clear();
                sub.push_back(remaining[0]);
                continue;
            }
            
            continue;
        }
        i++;
    }
    
    
    
    
}
/*
    To initialise the wall pressure, we take the neighbouring particles which 
    are not wall particles and take the average of their pressure
 
    initPressure and the neighbour search must be run before this and 
    the wall must have been added before the fluid
 */
void initWallPressure(std::vector<Particle*> plist, infoModule* module)
{
    double closestR, r;
    Particle* closest;
    int check;
    for (int i = 0 ; i < module->nWallPar; i++)
    {
        check = 0;
        if (plist[i]->neighbours.size() > 0)
        {
            closestR = 2*module->h;
            for (int j = 0; j < plist[i]->neighbours.size(); j++)
            {
                if (plist[i]->neighbours[j]->iswall == 0)
                {
                    r = plist[i]->neighboursdist[j];
                    if (r<closestR) {
                        closestR = r;
                        closest = plist[i]->neighbours[j];
                        check = 1;
                    }
                }
            }
            if (check ==1)
            {
                plist[i]->pressure[0] = closest->pressure[0] + module->deltax * module->rho0 * 9.81;
            }
            
        }
        
       
        
        
        
    }
}









