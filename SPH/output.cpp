//
//  output.cpp
//  SPH
//
//  Created by Sam Hunter on 06/11/2014.
//  Copyright (c) 2014 Sam Hunter. All rights reserved.
//

#include "output.h"

void writeParticles(std::vector<Particle*> plist, infoModule* module)
{
    using namespace std;
    
    ofstream myfile;
    
    string baseName = "Par";
    char NUM[4];
    int c = sprintf(NUM,"%04d",module->fileN);
    
    myfile.open ("/Users/Sam/Desktop/SPH/SPH/output/" +baseName + NUM+ ".txt");
    
    for (int i = 0; i< plist.size(); i++)
    {
        myfile << plist[i]->position[0] << " " << plist[i]->position[1] << " " <<plist[i]->position[2] << " " << plist[i]->vel[0] << " " << plist[i]->vel[1] << " " <<plist[i]->vel[2] << " " <<plist[i]->pressure[0] <<endl;
    }
    
    cout << "Written to file: " << baseName + NUM+ ".txt" << endl;
    
    myfile.close();
    
   
    
}