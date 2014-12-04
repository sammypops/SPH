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


void pressureTimeStep(std::vector<Particle*> plist, infoModule* module)
{
    for (int i = 0; i < plist.size(); i++)
    {
        plist[i]->pressure[0] = pow(module->cs,2)*(plist[i]->density[0]-module->rho0) ;
        
    }
}

void densityTimeStep(std::vector<Particle*> plist, infoModule* module)
{
    double t = module->deltat;
    double ddt ,rho, d;
    findDrhodt(plist, module);
    
    for (int i = 0; i< plist.size(); i++)
    {
        ddt = plist[i]->drhodt[0];
        
        rho =plist[i]->density[0];
        
        d = rho + t*ddt;
        
        plist[i]->density[0] = plist[i]->density[0] + t*plist[i]->drhodt[0];
    }
    
}

void PTSMT8(std::vector<Particle*> plist, infoModule* module)
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
    std::thread first (pressureTimeStep, minilist1, module);
    //2
    for (int i = int(ceil(plist.size()/8)); i<plist.size()/4; i++)
    {
        minilist2.push_back(plist[i]);
    }
    std::thread second (pressureTimeStep, minilist2,module);
    //3
    for (int i = int(ceil(plist.size()/4)); i<3*plist.size()/8; i++)
    {
        minilist3.push_back(plist[i]);
    }
    std::thread third (pressureTimeStep, minilist3, module);
    //4
    for (int i = int(ceil(3*plist.size()/8)); i<4*plist.size()/8; i++)
    {
        minilist4.push_back(plist[i]);
    }
    std::thread fourth (pressureTimeStep, minilist4, module);
    //5
    for (int i = int(ceil(4*plist.size()/8)); i<5*plist.size()/8; i++)
    {
        minilist5.push_back(plist[i]);
    }
    std::thread fifth (pressureTimeStep, minilist5, module);
    //6
    for (int i = int(ceil(5*plist.size()/8)); i<6*plist.size()/8; i++)
    {
        minilist6.push_back(plist[i]);
    }
    std::thread sixth (pressureTimeStep, minilist6,module);
    //7
    for (int i = int(ceil(6*plist.size()/8)); i<7*plist.size()/8; i++)
    {
        minilist7.push_back(plist[i]);
    }
    std::thread seventh (pressureTimeStep, minilist7, module);
    //8
    for (int i = int(ceil(7*plist.size()/8)); i<plist.size(); i++)
    {
        minilist8.push_back(plist[i]);
    }
    std::thread eighth (pressureTimeStep, minilist8, module);
    
    
    
    
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
    third.join();
    fourth.join();
    fifth.join();
    sixth.join();
    seventh.join();
    eighth.join();
    
}

void DTSMT8(std::vector<Particle*> plist, infoModule* module)
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
    std::thread first (densityTimeStep, minilist1, module);
    //2
    for (int i = int(ceil(plist.size()/8)); i<plist.size()/4; i++)
    {
        minilist2.push_back(plist[i]);
    }
    std::thread second (densityTimeStep, minilist2,module);
    //3
    for (int i = int(ceil(plist.size()/4)); i<3*plist.size()/8; i++)
    {
        minilist3.push_back(plist[i]);
    }
    std::thread third (densityTimeStep, minilist3, module);
    //4
    for (int i = int(ceil(3*plist.size()/8)); i<4*plist.size()/8; i++)
    {
        minilist4.push_back(plist[i]);
    }
    std::thread fourth (densityTimeStep, minilist4, module);
    //5
    for (int i = int(ceil(4*plist.size()/8)); i<5*plist.size()/8; i++)
    {
        minilist5.push_back(plist[i]);
    }
    std::thread fifth (densityTimeStep, minilist5, module);
    //6
    for (int i = int(ceil(5*plist.size()/8)); i<6*plist.size()/8; i++)
    {
        minilist6.push_back(plist[i]);
    }
    std::thread sixth (densityTimeStep, minilist6,module);
    //7
    for (int i = int(ceil(6*plist.size()/8)); i<7*plist.size()/8; i++)
    {
        minilist7.push_back(plist[i]);
    }
    std::thread seventh (densityTimeStep, minilist7, module);
    //8
    for (int i = int(ceil(7*plist.size()/8)); i<plist.size(); i++)
    {
        minilist8.push_back(plist[i]);
    }
    std::thread eighth (densityTimeStep, minilist8, module);
    
    
    
    
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
    third.join();
    fourth.join();
    fifth.join();
    sixth.join();
    seventh.join();
    eighth.join();
    
}