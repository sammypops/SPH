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
    std::array<double, 3> accel, nextAccel, prevAccel; // acceleration storage for timestep
    std::array<double, 3> drhodt; // change in density over time
    std::array<double,1> m; // mass of particle
    std::array<double, 1>  pressure;
    std::array<double, 3> delP; // the pressure gradient
    std::array<double, 3> dr; // the distance moved in the timestep
    std::array<double, 1>  density; // the current density
    
    
    std::vector<Particle*> neighbours;
    std::vector<double> neighboursdist;
    
    int iswall; // 1 = wall, 0 = fluid
    
public:
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