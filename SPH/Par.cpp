//
//  Par.cpp
//  SPH
//
//  Created by Sam Hunter on 26/10/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//


#include <vector>
#include <array>


class Particle {
    int a;
public:
    std::array<double, 2>  position;
    std::array<double, 2>  vel;
    std::array<double, 1> drhodt;
    std::array<double,1> m;
    std::vector<Particle*> neighbours;
    std::vector<double> neighboursdist;
    
public:
    Particle()
    {
        position[0] = 0.0;
        position[1] = 0.0;
        
        vel[0] = 0.0;
        vel[1] = 0.0;
    }
    Particle(std::array<double, 5> init)// {x,y,u,v,m}
    {
        position[0] = init[0];
        position[1] = init[1];
        
        vel[0] = init[2];
        vel[1] = init[3];
        
        m[0] = init[4];
    }
    void resetneighbours()
    {
        neighbours.clear();
        neighboursdist.clear();
    }
    
    
};