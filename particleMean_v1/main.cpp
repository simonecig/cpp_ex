/*
** Create a function "main" taking the file name from the command string,
** reading the file and calling the dump and clear functions.
*/

#include <iostream>
#include <fstream>
struct Event;
struct Particle;

Event* read(std::ifstream &file);
void dump(const Event &ev);
void clear(const Event *ev);
bool add(const Event &ev, float minMass, float maxMass,
         double &sumMass, double &sumSqMass);


int main(int argc, char *argv[]) {
    int acceptedEvNum = 0;
    double sumInvMass = 0;
    double sumSqInvMass = 0;
    double meanInvMass = 0;
    double rmsInvMass = 0;
    const float MINMASS = 0.490;
    const float MAXMASS = 0.505;

    // get file name
    const char* fname = argv[1];

    // check if file exists
    std::ifstream file(fname);
    if(!file){
        std::cout << "File not found" << std::endl;
        return 1;
    }

    // loop over events
    Event* ev;
    while( (ev = read(file)) != nullptr){
        //dump(*ev);
        if( add(*ev, MINMASS, MAXMASS, sumInvMass, sumSqInvMass) )
            acceptedEvNum++;
        clear(ev);
    }
    meanInvMass = sumSqInvMass / acceptedEvNum;
    rmsInvMass = 0;
    std::cout << meanInvMass << "\t" << rmsInvMass << std::endl;
    return 0;
}
