//
//  Par.cpp
//  SPH
//
//  Created by Sam Hunter on 26/10/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//


#include <array>
#include <vector>


class Particle {
    int a;
public:
    std::array<double, 2>  position;
    std::array<double, 2>  vel;
    std::array<double, 1> drhodt;
    std::array<double,1> m;
    std::array<double, 1>  pressure;
    std::array<double, 1>  density;
    std::vector<Particle*> neighbours;
    std::vector<double> neighboursdist;
    
    int iswall;
    
public:
    Particle()
    {
        position[0] = 0.0;
        position[1] = 0.0;
        
        vel[0] = 0.0;
        vel[1] = 0.0;
    }
    Particle(std::array<double, 2> posn, std::array<double, 2> velocity, std::array<double, 3> init)// {x,y},{u,v},{m,pressure,density}
    {
        position[0] = posn[0];
        position[1] = posn[1];
        
        vel[0] = velocity[0];
        vel[1] = velocity[1];
        
        m[0] = init[0];
        
        pressure[0] = init[1];
        density[0] = init[2];
    }
    Particle(int wall, std::array<double, 2> posn, std::array<double, 3> init)// {x,y},{m,pressure,density}
    {
        
    }
    void resetneighbours()
    {
        neighbours.clear();
        neighboursdist.clear();
    }
    
    
};