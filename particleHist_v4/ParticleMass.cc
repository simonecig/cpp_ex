#include "ParticleMass.h"
#include "Constants.h"
#include "MassMean.h"
#include "Event.h"
#include "TFile.h"
#include "TH1F.h"
#include "AnalysisFactory.h"
#include "AnalysisInfo.h"
#include "ParticleReco.h"

#include <iostream>

// concrete factory to create a ParticleMass analyzer
class ParticleMassFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleMassFactory(): AnalysisFactory::AbsFactory( "plot" ) {}
  // create a ParticleMass when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new ParticleMass(info);
  }
};
// create a global ElementRecoFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ElementRecoFactory will be available with name "plot".
static ParticleMassFactory er;


ParticleMass::ParticleMass(const AnalysisInfo* info):
 AnalysisSteering(info){}

ParticleMass::~ParticleMass(){}

void ParticleMass::beginJob(){
    // create pointer for 2 decay modes
    pList.reserve(2);
    pCreate("massK0",0.495, 0.500);
    pCreate("massLambda0", 1.115, 1.116);
    return;
}

void ParticleMass::endJob(){

    // save current working area
    TDirectory* currentDir = gDirectory;
    // open histogram file
    TFile* file = new TFile(aInfo->value("plot").c_str(), "CREATE");

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
    currentDir->cd();

    return;
}

void ParticleMass::update(const Event &ev){
    static ParticleReco* partRec = ParticleReco::instance();
    // loop over particles
    for(auto part: pList){
        // call add function for each MassMean
        // and fill Histogram with invariant mass
        if(part->mmPtr->add(ev))
            part->func->Fill(partRec->getMass());
    }
}

void ParticleMass::pCreate(const std::string& name, float min,
                           float max){
    int nBins = 100;

    // create and store particle
    Particle *p = new Particle;
    p->mmPtr = new MassMean(min,max);
    p->func = new TH1F(&name[0], &name[0], nBins,min, max);
    pList.push_back(p);

}
