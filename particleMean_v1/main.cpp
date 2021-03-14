#include <iostream>
#include <fstream>
#include <cmath>

struct Event;

Event* read(std::ifstream &file);
void dump(const Event &ev);
void clear(const Event *ev);
bool add(const Event &ev, float minMass, float maxMass,
         double &sumMass, double &sumSqMass);


int main(int argc, char *argv[]) {

    int acceptedEvNum = 0; // number of events in range
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
        // add event and compute mass if in range
        if(add(*ev, MINMASS, MAXMASS, sumInvMass, sumSqInvMass))
            acceptedEvNum++;
        clear(ev);
    }
    // compute mean and rms
    meanInvMass = sumInvMass*1.0 / acceptedEvNum;
    double varInvMass = sumSqInvMass*1.0/acceptedEvNum -
                       pow(meanInvMass,2);
    if(varInvMass > 0)
        rmsInvMass = sqrt(varInvMass);
    else
        rmsInvMass = 0;

    // add back MINMASS
    meanInvMass +=(MINMASS);

    // print results
    std::cout << meanInvMass << "\t" << rmsInvMass << std::endl;

    return 0;
}
