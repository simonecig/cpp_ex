#include "ParticleMass.h"
#include "Constants.h"
#include "MassMean.h"
#include <iostream>

ParticleMass::ParticleMass(){}
ParticleMass::~ParticleMass(){}

void ParticleMass::beginJob(){
    // create pointer for 2 decay modes
    pList.reserve(2);
    pList.push_back(new MassMean(0.495, 0.500));
    pList.push_back(new MassMean(1.115, 1.116));
    return;
}

void ParticleMass::endJob(){
    // for each MassMean compute and print mean, rms
    for(auto mMean: pList){
        mMean->compute();
        const double mean = mMean->mMean();
        const double rms = mMean->mRMS();
        std::cout << "mean\t" << mean
                  << "\nrms\t" << rms << std::endl;
    }
    return;
}

void ParticleMass::process(const Event &ev){
    // call add function for each MassMean
    for(auto mMean: pList)
       mMean->add(ev);
}
