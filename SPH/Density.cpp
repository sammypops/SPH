//
//  Density.cpp
//  SPH
//
//  Created by Sam Hunter on 04/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "Density.h"

void findDensity(std::vector<Particle*> plist, infoModule* module)
{
    double sum, r, dxdr, dkernel;
    
    for (int n = 0; n<plist.size(); n++)
    {
        sum = 0.0;
        
        for (int m=0; m<plist[n]->neighbours.size(); m++)
        {
            r = plist[n]->neighboursdist[m];
            if (plist[n]->neighboursdist[m] == 0)
            {
                continue;
            }
            dxdr = (plist[n]->position[0] - plist[n]->neighbours[m]-> position[0])/r;
            dkernel = wendkernel(r,module);
            //dkernel = quadkernel(r,h);
            //dkernel = gausskernel(r,h);
            sum = sum + (plist[n]->vel[0] - plist[n]->neighbours[m]->vel[0])*dxdr*dkernel*plist[n]->neighbours[m]->m[0];
        }
        // write dp/dt after summing over all of the particles
        plist[n]->drhodt[0] = sum;
    }

}