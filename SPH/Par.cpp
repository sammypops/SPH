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
    std::array<double, 3>  position;
    std::array<double, 3>  vel;
    std::array<double, 3> accel;
    std::array<double, 3> drhodt;
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
        
        iswall = 0;
        
        vel[0] = 0.0;
        vel[1] = 0.0;
    }
    Particle(std::array<double, 3> posn, std::array<double, 3> velocity, std::array<double, 3> init)// {x,y},{u,v},{m,pressure,density}
    {
        iswall = 0;
        
        accel = {0,0};
        
        position[0] = posn[0];
        position[1] = posn[1];
        position[2] = posn[2];
        
        vel[0] = velocity[0];
        vel[1] = velocity[1];
        vel[2] = velocity[2];
        
        m[0] = init[0];
        
        pressure[0] = init[1];
        density[0] = init[2];
    }
    // Create a wall particle
    Particle(int wall, std::array<double, 3> posn, std::array<double, 3> init)// {x,y},{m,pressure,density}
    {
        iswall = wall;
        position[0] = posn[0];
        position[1] = posn[1];
        position[2] = posn[2];
        
        m[0] = init[0];
        
        pressure[0] = init[1];
        density[0] = init[2];
    }
    void resetneighbours()
    {
        neighbours.clear();
        neighboursdist.clear();
    }
    
    
};