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
            sum[Dim] = sum[Dim] - (plist[i]->neighbours[j]->m[0]*(p_j/pow(rho_j, 2) + p_i/pow(rho_i, 2)+ visc) * dxdr * dkernel);
        }
        
        
    }
    return sum;

}

void findAccel(std::vector<Particle*> plist, infoModule* module)
{
    
    std::array<double, 3> dvdt;
    
    
    for (int i = 0; i<plist.size(); i++)
    {
        if (plist[i]->iswall == 1)
        {
            continue;
        }
        
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
        
        if (plist[i]->iswall == 1)
        {
            continue;
        }
        
        dvdt.fill(0.0);
        
        
        
        dvdt = acceleration(i, plist, module);
        
        // gravity acts in y in 2d and in z in 3d
        dvdt[module->nDim -1] = dvdt[module->nDim -1] - 9.81;
            
        plist[i]->nextAccel = dvdt;
        
        
    }
    
}

void FNAMT8(std::vector<Particle*> plist, infoModule* module)
{
    std::vector<Particle*> minilist1;
    std::vector<Particle*> minilist2;
    std::vector<Particle*> minilist3;
    std::vector<Particle*> minilist4;
    std::vector<Particle*> minilist5;
    std::vector<Particle*> minilist6;
    std::vector<Particle*> minilist7;
    std::vector<Particle*> minilist8;
    
    //1
    for (int i = 0; i<plist.size()/8; i++)
    {
        minilist1.push_back(plist[i]);
    }
    std::thread first (findNextAccel, minilist1, module);
    //2
    for (int i = int(ceil(plist.size()/8)); i<plist.size()/4; i++)
    {
        minilist2.push_back(plist[i]);
    }
    std::thread second (findNextAccel, minilist2,module);
    //3
    for (int i = int(ceil(plist.size()/4)); i<3*plist.size()/8; i++)
    {
        minilist3.push_back(plist[i]);
    }
    std::thread third (findNextAccel, minilist3, module);
    //4
    for (int i = int(ceil(3*plist.size()/8)); i<4*plist.size()/8; i++)
    {
        minilist4.push_back(plist[i]);
    }
    std::thread fourth (findNextAccel, minilist4, module);
    //5
    for (int i = int(ceil(4*plist.size()/8)); i<5*plist.size()/8; i++)
    {
        minilist5.push_back(plist[i]);
    }
    std::thread fifth (findNextAccel, minilist5, module);
    //6
    for (int i = int(ceil(5*plist.size()/8)); i<6*plist.size()/8; i++)
    {
        minilist6.push_back(plist[i]);
    }
    std::thread sixth (findNextAccel, minilist6,module);
    //7
    for (int i = int(ceil(6*plist.size()/8)); i<7*plist.size()/8; i++)
    {
        minilist7.push_back(plist[i]);
    }
    std::thread seventh (findNextAccel, minilist7, module);
    //8
    for (int i = int(ceil(7*plist.size()/8)); i<plist.size(); i++)
    {
        minilist8.push_back(plist[i]);
    }
    std::thread eighth (findNextAccel, minilist8, module);
    
    
    
    
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
    third.join();
    fourth.join();
    fifth.join();
    sixth.join();
    seventh.join();
    eighth.join();
    
}