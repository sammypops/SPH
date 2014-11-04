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
    for (int n = 0; n<listofparticles.size(); n++)
    {
        sum = 0.0;
        
        for (int m=0; m<listofparticles[n]->neighbours.size(); m++)
        {
            r = listofparticles[n]->neighboursdist[m];
            if (listofparticles[n]->neighboursdist[m] == 0)
            {
                continue;
            }
            xr = (listofparticles[n]->position[0] - listofparticles[n]->neighbours[m]-> position[0])/r;
            dkernel = wendkernel(r,&simInfo);
            //dkernel = quadkernel(r,h);
            //dkernel = gausskernel(r,h);
            sum = sum + (listofparticles[n]->vel[0] - listofparticles[n]->neighbours[m]->vel[0])*xr*dkernel*listofparticles[n]->neighbours[m]->m[0];
        }
        // write dp/dt after summing over all of the particles
        listofparticles[n]->drhodt[0] = sum;
    }

}