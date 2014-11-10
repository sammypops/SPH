//
//  Momentum.cpp
//  SPH
//
//  Created by Sam Hunter on 03/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "Momentum.h"

double viscosity(int i, int j,std::vector<Particle*> plist, infoModule* module)
{
    double visc;
    double alpha, mu, cbar, rhobar;
    double m;
    
    m = 0.0;
    
    for (int Dim = 0; Dim<module->nDim; Dim++)
    {
        m = m + (plist[i]->position[Dim] - plist[i]->neighbours[j]->position[Dim]) *(plist[i]->vel[Dim] - plist[i]->neighbours[j]->vel[Dim]);
    }
    if (m > 0)
    {
        visc = 0.0;
        return visc;
    }
    
    alpha = 0.1;
    
    mu = (module->h* m )/(plist[i]->neighboursdist[j] + 0.01*pow(module->h, 2));
    
    rhobar = (plist[i]->density[0] + plist[i]->neighbours[j]->density[0])/2;
    
    cbar = module->cs;
    
    visc = (-alpha*cbar*mu)/rhobar;
    
    return visc;
    
}

std::array<double,3> acceleration (int i,std::vector<Particle*> plist, infoModule* module)
{
    std::array<double, 3> sum;
    double r;
    double dkernel;
    double dxdr;
    double p_i, p_j, rho_i, rho_j;
    double visc;
    
    sum.fill(0.0);
    
    p_i = plist[i]->pressure[0];
    rho_i = plist[i]->density[0];
    
    for (int j = 0; j<plist[i]->neighbours.size(); j++)
    {
        r = plist[i]->neighboursdist[j];
        if (r == 0.0)
        {
            continue;
        }
        visc = viscosity(i,j,plist,module);
        dkernel = wendkernel(r,  module);
        p_j = plist[i]->neighbours[j]->pressure[0];
        rho_j = plist[i]->neighbours[j]->density[0];
        
        for (int Dim = 0; Dim < module->nDim; Dim++)
        {
            dxdr = (plist[i]->position[Dim] - plist[i]->neighbours[j]-> position[Dim])/r;
            //momentum eqn
            sum[Dim] = sum[Dim] - (plist[i]->neighbours[j]->m[0]*(p_j/pow(rho_j, 2) + p_i/pow(rho_i, 2)+ viscosity(i, j, plist, module)) * dxdr * dkernel);
        }
        
        
    }
    return sum;

}

void findAccel(std::vector<Particle*> plist, infoModule* module)
{
    
    std::array<double, 3> dvdt;
    
    
    for (int i = 0; i<plist.size(); i++)
    {
        
        dvdt.fill(0.0);
        
        dvdt = acceleration(i, plist, module);
        
        // gravity acts in y in 2d and in z in 3d
        dvdt[module->nDim -1] = dvdt[module->nDim -1] - 9.81;
    
        
        plist[i]->prevAccel = plist[i]->accel;
        plist[i]->accel = dvdt;
        
    }
    
}

void findNextAccel(std::vector<Particle*> plist, infoModule* module)
{
    std::array<double, 3> dvdt;
    
    
    for (int i = 0; i<plist.size(); i++)
    {
        
        dvdt.fill(0.0);
        
        dvdt = acceleration(i, plist, module);
        
        // gravity acts in y in 2d and in z in 3d
        dvdt[module->nDim -1] = dvdt[module->nDim -1] - 9.81;
            
        plist[i]->nextAccel = dvdt;
        
        
    }
    
}