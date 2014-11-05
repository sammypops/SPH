//
//  Density.cpp
//  SPH
//
//  Created by Sam Hunter on 04/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "Density.h"

void findDrhodt(std::vector<Particle*> plist, infoModule* module)
{
    //std::array<double, 3> sum;
    double  r, dxdr, dkernel, sum;
    
    for (int n = 0; n<plist.size(); n++)
    {
        sum = 0.0;
        /*
        sum[0] = 0.0;
        sum[1] = 0.0;
        sum[2] = 0.0;
        */
        
        for (int m=0; m<plist[n]->neighbours.size(); m++)
        {
            r = plist[n]->neighboursdist[m];
            if (plist[n]->neighboursdist[m] == 0)
            {
                continue;
            }
            
            dkernel = wendkernel(r,module);
            //dkernel = quadkernel(r,h);
            //dkernel = gausskernel(r,h);
            
            //*****************************************
            //is this right?
            //*****************************************
            for (int Dim = 0; Dim < module->nDim; Dim++)
            {
                dxdr = (plist[n]->position[Dim] - plist[n]->neighbours[m]-> position[Dim])/r;
                sum = sum + (plist[n]->vel[Dim] - plist[n]->neighbours[m]->vel[Dim])*dxdr*dkernel*plist[n]->neighbours[m]->m[0];
            }
            
        }
        
        // write drho/dt after summing over all of the particles
        plist[n]->drhodt[0] = sum;
    }

}

void findDelP(std::vector<Particle*> plist, infoModule* module)
{
    double  r, dxdr, dkernel;
    std::array<double,3> sum;
    
    for (int n = 0; n<plist.size(); n++)
    {
         sum[0] = 0.0;
         sum[1] = 0.0;
         sum[2] = 0.0;
        
        for (int m=0; m<plist[n]->neighbours.size(); m++)
        {
            r = plist[n]->neighboursdist[m];
            if (plist[n]->neighboursdist[m] == 0)
            {
                continue;
            }
            
            dkernel = wendkernel(r,module);
            //dkernel = quadkernel(r,h);
            //dkernel = gausskernel(r,h);
            
            //*****************************************
            //is this right?
            //*****************************************
            for (int Dim = 0; Dim < module->nDim; Dim++)
            {
                dxdr = (plist[n]->position[Dim] - plist[n]->neighbours[m]-> position[Dim])/r;
                sum[Dim] = sum[Dim] + (plist[n]->pressure[0] - plist[n]->neighbours[m]->pressure[0])*dxdr*dkernel*plist[n]->neighbours[m]->m[0]/plist[n]->neighbours[m]->density[0];
            }
            
        }
        
        // write drho/dt after summing over all of the particles
        plist[n]->delP = sum;
    }
    
}