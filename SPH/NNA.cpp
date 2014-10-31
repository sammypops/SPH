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
/****************************************************
 *******DEPRECATED USE MULTI THREAD NEIGHBOUR********
 ****************************************************
 */
// 4 thread brute force neighbour finding algorithm
void findNeighboursMT4(std::vector<Particle*> plist, double h)
{
    std::vector<Particle*> minilist1;
    std::vector<Particle*> minilist2;
    std::vector<Particle*> minilist3;
    std::vector<Particle*> minilist4;
    
    for (int i = 0; i<plist.size()/4; i++)
    {
        minilist1.push_back(plist[i]);
    }
    std::thread first (findNeighbours, minilist1, h);
    
    for (int i = int(ceil(plist.size()/4)); i<plist.size()/2; i++)
    {
        minilist2.push_back(plist[i]);
    }
    std::thread second (findNeighbours, minilist2,h);
    
    for (int i = int(ceil(plist.size()/2)); i<3*plist.size()/4; i++)
    {
        minilist3.push_back(plist[i]);
    }
    std::thread third (findNeighbours, minilist3, h);
    
    for (int i = int(ceil(3*plist.size()/4)); i<plist.size(); i++)
    {
        minilist4.push_back(plist[i]);
    }
    std::thread fourth (findNeighbours, minilist4, h);
    
    
    
    
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
    third.join();
    fourth.join();
    
}
/****************************************************
 *******DEPRECATED USE MULTI THREAD NEIGHBOUR********
 ****************************************************
 */
// 8 thread brute force neighbour finding algorithm
void findNeighboursMT8(std::vector<Particle*> plist, double h)
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
    std::thread first (findNeighbours, minilist1, h);
    //2
    for (int i = int(ceil(plist.size()/8)); i<plist.size()/4; i++)
    {
        minilist2.push_back(plist[i]);
    }
    std::thread second (findNeighbours, minilist2,h);
    //3
    for (int i = int(ceil(plist.size()/4)); i<3*plist.size()/8; i++)
    {
        minilist3.push_back(plist[i]);
    }
    std::thread third (findNeighbours, minilist3, h);
    //4
    for (int i = int(ceil(3*plist.size()/8)); i<4*plist.size()/8; i++)
    {
        minilist4.push_back(plist[i]);
    }
    std::thread fourth (findNeighbours, minilist4, h);
    //5
    for (int i = int(ceil(4*plist.size()/8)); i<5*plist.size()/8; i++)
    {
        minilist5.push_back(plist[i]);
    }
    std::thread fifth (findNeighbours, minilist5, h);
    //6
    for (int i = int(ceil(5*plist.size()/8)); i<6*plist.size()/8; i++)
    {
        minilist6.push_back(plist[i]);
    }
    std::thread sixth (findNeighbours, minilist6,h);
    //7
    for (int i = int(ceil(6*plist.size()/8)); i<7*plist.size()/8; i++)
    {
        minilist7.push_back(plist[i]);
    }
    std::thread seventh (findNeighbours, minilist7, h);
    //8
    for (int i = int(ceil(7*plist.size()/8)); i<plist.size(); i++)
    {
        minilist8.push_back(plist[i]);
    }
    std::thread eighth (findNeighbours, minilist8, h);
    
    
    
    
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
    third.join();
    fourth.join();
    fifth.join();
    sixth.join();
    seventh.join();
    eighth.join();
    
}

void FNMT8(std::vector<Particle*> plist, double h)
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
    std::thread first (FN, minilist1, plist, h);
    //2
    for (int i = int(ceil(plist.size()/8)); i<plist.size()/4; i++)
    {
        minilist2.push_back(plist[i]);
    }
    std::thread second (FN, minilist2, plist,h);
    //3
    for (int i = int(ceil(plist.size()/4)); i<3*plist.size()/8; i++)
    {
        minilist3.push_back(plist[i]);
    }
    std::thread third (FN, minilist3, plist, h);
    //4
    for (int i = int(ceil(3*plist.size()/8)); i<4*plist.size()/8; i++)
    {
        minilist4.push_back(plist[i]);
    }
    std::thread fourth (FN, minilist4, plist, h);
    //5
    for (int i = int(ceil(4*plist.size()/8)); i<5*plist.size()/8; i++)
    {
        minilist5.push_back(plist[i]);
    }
    std::thread fifth (FN, minilist5, plist, h);
    //6
    for (int i = int(ceil(5*plist.size()/8)); i<6*plist.size()/8; i++)
    {
        minilist6.push_back(plist[i]);
    }
    std::thread sixth (FN, minilist6, plist,h);
    //7
    for (int i = int(ceil(6*plist.size()/8)); i<7*plist.size()/8; i++)
    {
        minilist7.push_back(plist[i]);
    }
    std::thread seventh (FN, minilist7, plist, h);
    //8
    for (int i = int(ceil(7*plist.size()/8)); i<plist.size(); i++)
    {
        minilist8.push_back(plist[i]);
    }
    std::thread eighth (FN, minilist8, plist, h);
    
    
    
    
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
void findNeighbours(std::vector<Particle*> plist, double h)
{
    double r = 0.0;
    for (int i = 0; i < plist.size(); i++)
    {
        plist[i]->resetneighbours();
        for (int j = 0; j < plist.size(); j++)
        {
            
            if (i == j)
            {
                continue;
            }
            r = pDist(plist[i], plist[j]);
            
            if (fabs(r) < 2*h-0.0000001 ) // if the particles i and j are close add them to the list of neighbours for particle i
            {
                plist[i]->neighbours.push_back(plist[j]);
                plist[i]->neighboursdist.push_back(r);
            }
            
        }
    }
}

void FN(std::vector<Particle*> plist, std::vector<Particle*> allParticles, double h)
{
    double r = 0.0;
    for (int i = 0; i < plist.size(); i++)
    {
        plist[i]->resetneighbours();
        for (int j = 0; j < allParticles.size(); j++)
        {
            
            if (i == j)
            {
                continue;
            }
            r = pDist(plist[i], allParticles[j]);
            
            if (fabs(r) < 2*h-0.0000001 ) // if the particles i and j are close add them to the list of neighbours for particle i
            {
                plist[i]->neighbours.push_back(allParticles[j]);
                plist[i]->neighboursdist.push_back(r);
            }
            
        }
    }
}

// 8 threaded recursive neighbour update
void updateNeighboursMT8(std::vector<Particle*> plist, double h)
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
    std::thread first (updateNeighbours, minilist1, h);
    //2
    for (int i = int(ceil(plist.size()/8)); i<plist.size()/4; i++)
    {
        minilist2.push_back(plist[i]);
    }
    std::thread second (updateNeighbours, minilist2,h);
    //3
    for (int i = int(ceil(plist.size()/4)); i<3*plist.size()/8; i++)
    {
        minilist3.push_back(plist[i]);
    }
    std::thread third (updateNeighbours, minilist3, h);
    //4
    for (int i = int(ceil(3*plist.size()/8)); i<4*plist.size()/8; i++)
    {
        minilist4.push_back(plist[i]);
    }
    std::thread fourth (updateNeighbours, minilist4, h);
    //5
    for (int i = int(ceil(4*plist.size()/8)); i<5*plist.size()/8; i++)
    {
        minilist5.push_back(plist[i]);
    }
    std::thread fifth (updateNeighbours, minilist5, h);
    //6
    for (int i = int(ceil(5*plist.size()/8)); i<6*plist.size()/8; i++)
    {
        minilist6.push_back(plist[i]);
    }
    std::thread sixth (updateNeighbours, minilist6,h);
    //7
    for (int i = int(ceil(6*plist.size()/8)); i<7*plist.size()/8; i++)
    {
        minilist7.push_back(plist[i]);
    }
    std::thread seventh (updateNeighbours, minilist7, h);
    //8
    for (int i = int(ceil(7*plist.size()/8)); i<plist.size(); i++)
    {
        minilist8.push_back(plist[i]);
    }
    std::thread eighth (updateNeighbours, minilist8, h);
    
    
    
    
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
void updateNeighbours (std::vector<Particle*> plist, double h)
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
                    if (fabs(r) < 2*h-0.0000001 ) // if the particles i and k are close add them to the list of newNeighbours for particle i
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
