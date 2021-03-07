#include "ParticleMass.h"
#include "Constants.h"
#include "MassMean.h"
#include <iostream>
#include "Event.h"
#include "TFile.h"
#include "TH1F.h"

double mass( const Event& ev );
// TODO: numero bin?????
ParticleMass::ParticleMass(){}
ParticleMass::~ParticleMass(){}

void ParticleMass::beginJob(){
    // create pointer for 2 decay modes
    pList.reserve(2);
    pCreate("K0",0.495, 0.500);
    pCreate("Lambda0", 1.115, 1.116);
    return;
}

void ParticleMass::endJob(){

    // save current working area
    TDirectory* currentDir = gDirectory;
    // open histogram file
    TFile* file = new TFile("hist.root", "RECREATE");

    // for each MassMean compute and print mean, rms
    for(auto part: pList){
        // compute
        part->mmPtr->compute();
        const unsigned int nPart = part->mmPtr->nEvents();
        const double mean = part->mmPtr->mMean();
        const double rms = part->mmPtr->mRMS();
        // print
        std::cout << "n\t" << nPart << "\n"
                  << "mean\t" << mean << "\n"
                  << "rms\t" << rms << "\n";
        // save TH1F
        part->func->Write();
    }

    // close file and delete pointer
    file->Close();
    delete file;

    return;
}

void ParticleMass::process(const Event &ev){
    // loop over particles
    for(auto part: pList){
        // call add function for each MassMean
        // and fill Histogram with invariant mass
        if(part->mmPtr->add(ev))
            part->func->Fill(mass(ev));
    }
}

void ParticleMass::pCreate(const std::string& name, float min,
                           float max){
    int nBins = 10; // TODO: maybe not...

    // create and store particle
    Particle *p = new Particle;
    p->mmPtr = new MassMean(min,max);
    p->func = new TH1F(&name[0], &name[0], nBins,min, max);
    pList.push_back(p);

}
