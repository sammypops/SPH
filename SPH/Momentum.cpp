//
//  Momentum.cpp
//  SPH
//
//  Created by Sam Hunter on 03/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "Momentum.h"

void momentum(std::vector<Particle*> plist, infoModule* module)
{
    double r;
    double dkernel;
    std::array<double, 3> sum;
    double dxdr;
    double p_i, p_j, rho_i, rho_j;
    
    for (int i = 0; i<plist.size(); i++)
    {
        // don't include the wall particles maybe?
        if (plist[i]->iswall == 1) {
            continue;
        }
        sum[0] = 0.0;
        sum[1] = 0.0;
        sum[2] = 0.0;
        p_i = plist[i]->pressure[0];
        rho_i = plist[i]->density[0];
        for (int j = 0; j<plist[i]->neighbours.size(); j++)
        {
            r = plist[i]->neighboursdist[j];
            dkernel = wendkernel(r,  module);
            p_j = plist[i]->neighbours[j]->pressure[0];
            rho_j = plist[i]->neighbours[j]->density[0];
            
            for (int Dim = 0; Dim < module->nDim; Dim++)
            {
                dxdr = (plist[i]->position[Dim] - plist[i]->neighbours[j]-> position[Dim])/r;
                //momentum eqn
                sum[Dim] = sum[Dim] - (plist[i]->neighbours[j]->m[0]*(p_j/pow(rho_j, 2) + p_i/pow(rho_i, 2)) * dxdr * dkernel);
            }
            
            
        }
        
        for (int Dim = 0; Dim < module->nDim; Dim++)
        {
            plist[i]->accel[Dim] = sum[Dim];
        }
        
    }
    
}