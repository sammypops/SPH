//
//  Momentum.cpp
//  SPH
//
//  Created by Sam Hunter on 03/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "Momentum.h"

void momentum(std::vector<Particle*> plist, double h)
{
    double r;
    double dkernel;
    double xsum, ysum;
    double xr, yr;
    double p_i, p_j, rho_i, rho_j;
    for (int i = 0; i<plist.size(); i++)
    {
        xsum = 0.0;
        ysum = 0.0;
        p_i = plist[i]->pressure[0];
        rho_i = plist[i]->density[0];
        for (int j = 0; j<plist[i]->neighbours.size(); j++)
        {
            r = plist[i]->neighboursdist[j];
            dkernel = wendkernel(r,  h);
            xr = (plist[i]->position[0] - plist[i]->neighbours[j]-> position[0])/r;
            yr = (plist[i]->position[1] - plist[i]->neighbours[j]-> position[1])/r;
            
            p_j = plist[i]->neighbours[j]->pressure[0];
            rho_j = plist[i]->neighbours[j]->density[0];
            
            
            xsum = xsum - (plist[i]->neighbours[j]->m[0]*(p_j/pow(rho_j, 2) + p_i/pow(rho_i, 2)) * xr * dkernel);
            ysum = ysum - (plist[i]->neighbours[j]->m[0]*(p_j/pow(rho_j, 2) + p_i/pow(rho_i, 2)) * yr * dkernel);
            
        }
        
        plist[i]->vel[0] = plist[i]->vel[0] + xsum;
        plist[i]->vel[1] = plist[i]->vel[1] + ysum;
        
    }
    
}