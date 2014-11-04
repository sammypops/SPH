//
//  NNA.c
//  SPH
//
//  Created by Sam Hunter on 30/10/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include <stdio.h>
#include "NNA.h"

using namespace std;


//get's the euclidean norm of 2 particles
double pDist(Particle* p1, Particle* p2)
{
    double norm = 0.0;
    
    norm = sqrt(pow(p1->position[0] - p2->position[0],2)+pow(p1->position[1] - p2->position[1],2));
    
    return norm;
}
/*
    
*/

void FNMT8(std::vector<Particle*> plist, infoModule* module)
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
    std::thread first (FN, minilist1, plist, module);
    //2
    for (int i = int(ceil(plist.size()/8)); i<plist.size()/4; i++)
    {
        minilist2.push_back(plist[i]);
    }
    std::thread second (FN, minilist2, plist,module);
    //3
    for (int i = int(ceil(plist.size()/4)); i<3*plist.size()/8; i++)
    {
        minilist3.push_back(plist[i]);
    }
    std::thread third (FN, minilist3, plist, module);
    //4
    for (int i = int(ceil(3*plist.size()/8)); i<4*plist.size()/8; i++)
    {
        minilist4.push_back(plist[i]);
    }
    std::thread fourth (FN, minilist4, plist, module);
    //5
    for (int i = int(ceil(4*plist.size()/8)); i<5*plist.size()/8; i++)
    {
        minilist5.push_back(plist[i]);
    }
    std::thread fifth (FN, minilist5, plist, module);
    //6
    for (int i = int(ceil(5*plist.size()/8)); i<6*plist.size()/8; i++)
    {
        minilist6.push_back(plist[i]);
    }
    std::thread sixth (FN, minilist6, plist,module);
    //7
    for (int i = int(ceil(6*plist.size()/8)); i<7*plist.size()/8; i++)
    {
        minilist7.push_back(plist[i]);
    }
    std::thread seventh (FN, minilist7, plist, module);
    //8
    for (int i = int(ceil(7*plist.size()/8)); i<plist.size(); i++)
    {
        minilist8.push_back(plist[i]);
    }
    std::thread eighth (FN, minilist8, plist, module);
    
    
    
    
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
    third.join();
    fourth.join();
    fifth.join();
    sixth.join();
    seventh.join();
    eighth.join();
    
}


/* 
 Finds and allocates neighbours to particles in the given list
 by brute force, it takes a long time for large groups of particles
 but will not fail to get a comprehensive list of neighbours
*/

void FN(std::vector<Particle*> plist, std::vector<Particle*> allParticles, infoModule* module)
{
    double r = 0.0;
    for (int i = 0; i < plist.size(); i++)
    {
        plist[i]->resetneighbours();
        for (int j = 0; j < allParticles.size(); j++)
        {
            
            if (plist[i] == allParticles[j])
            {
                continue;
            }
            r = pDist(plist[i], allParticles[j]);
            
            if (fabs(r) < 2*module->h-0.0000001 ) // if the particles i and j are close add them to the list of neighbours for particle i
            {
                plist[i]->neighbours.push_back(allParticles[j]);
                plist[i]->neighboursdist.push_back(r);
            }
            
        }
    }
}

// 8 threaded recursive neighbour update
void updateNeighboursMT8(std::vector<Particle*> plist, infoModule* module)
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
    std::thread first (updateNeighbours, minilist1, module);
    //2
    for (int i = int(ceil(plist.size()/8)); i<plist.size()/4; i++)
    {
        minilist2.push_back(plist[i]);
    }
    std::thread second (updateNeighbours, minilist2,module);
    //3
    for (int i = int(ceil(plist.size()/4)); i<3*plist.size()/8; i++)
    {
        minilist3.push_back(plist[i]);
    }
    std::thread third (updateNeighbours, minilist3, module);
    //4
    for (int i = int(ceil(3*plist.size()/8)); i<4*plist.size()/8; i++)
    {
        minilist4.push_back(plist[i]);
    }
    std::thread fourth (updateNeighbours, minilist4, module);
    //5
    for (int i = int(ceil(4*plist.size()/8)); i<5*plist.size()/8; i++)
    {
        minilist5.push_back(plist[i]);
    }
    std::thread fifth (updateNeighbours, minilist5, module);
    //6
    for (int i = int(ceil(5*plist.size()/8)); i<6*plist.size()/8; i++)
    {
        minilist6.push_back(plist[i]);
    }
    std::thread sixth (updateNeighbours, minilist6,module);
    //7
    for (int i = int(ceil(6*plist.size()/8)); i<7*plist.size()/8; i++)
    {
        minilist7.push_back(plist[i]);
    }
    std::thread seventh (updateNeighbours, minilist7, module);
    //8
    for (int i = int(ceil(7*plist.size()/8)); i<plist.size(); i++)
    {
        minilist8.push_back(plist[i]);
    }
    std::thread eighth (updateNeighbours, minilist8, module);
    
    
    
    
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
    third.join();
    fourth.join();
    fifth.join();
    sixth.join();
    seventh.join();
    eighth.join();
    
}
/*
 Recursive neighbour search
 Takes the already existing neighbours to a particle and 
 searches through their neighbours for particles inside the
 kernel of the current particle 
 
 Very quick but will fail for two separate bodies of particles 
 colliding
 */
void updateNeighbours (std::vector<Particle*> plist, infoModule* module)
{
    double r = 0.0;
    std::vector<Particle*> newneighbours;
    std::vector<double> newneighboursdist;
    
    for (int i = 0; i<plist.size(); i++)
    {
        
        for (int j = 0; j<plist[i]->neighbours.size(); j++)
        {
            for (int k = 0; k < plist[i]->neighbours[j]->neighbours.size(); k++)
            {
                // if the neighbour's neighbours aren't already in the newNeighbours list then check if it's in the kernel. New neighbour can't be particle i.
                if (std::find(newneighbours.begin(), newneighbours.end(), plist[i]->neighbours[j]->neighbours[k]) == newneighbours.end() && plist[i] != plist[i]->neighbours[j]->neighbours[k])
                {
                    r = pDist(plist[i], plist[i]->neighbours[j]->neighbours[k]);
                    if (fabs(r) < 2*module->h-0.0000001 ) // if the particles i and k are close add them to the list of newNeighbours for particle i
                    {
                        newneighbours.push_back(plist[i]->neighbours[j]->neighbours[k]);
                        newneighboursdist.push_back(r);
                    }//if
                }//if
                
            }//k
            
        }//j
        
        
        plist[i]->neighbours = newneighbours;
        plist[i]->neighboursdist = newneighboursdist;
        
        // reset the newneighbour lists for the next particle
        newneighbours.clear();
        newneighboursdist.clear();
        
    }//i
    
    
}
