#include "ParticleLifetime.h"
#include "Constants.h"
#include "LifetimeFit.h"
#include "Event.h"
#include "TFile.h"
#include "TH1F.h"
#include "AnalysisFactory.h"
#include "AnalysisInfo.h"
#include "ProperTime.h"
#include <fstream>
#include <iostream>

// concrete factory to create a ParticleLifetime analyzer
class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "time" ) {}
  // create a ParticleLifetime when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new ParticleLifetime(info);
  }
};
// create a global ElementRecoFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ElementRecoFactory will be available with name "plot".
static ParticleLifetimeFactory er;


ParticleLifetime::ParticleLifetime(const AnalysisInfo* info):
 AnalysisSteering(info){}

ParticleLifetime::~ParticleLifetime(){}

void ParticleLifetime::beginJob(){
    // create pointer for 2 decay modes
    pList.reserve(2);
    std::ifstream file(aInfo->value("tranges").c_str());
    // read from file
    std::string name;
    double minMass, maxMass;
    double minTime, maxTime;
    double minScan, maxScan, scanStep;
    while (file >> name >> minMass >> maxMass >>
           minTime >> maxTime >>
           minScan >> maxScan >> scanStep){
        pCreate("time"+name, minMass, maxMass, minTime, maxTime,
                minScan, maxScan, scanStep);
    }
    //pCreate("timeK0",0.495, 0.500, 10.0,500.0);
    //pCreate("timeLambda0", 1.115, 1.116, 10.0, 1000.0);
    return;
}

void ParticleLifetime::endJob(){

    // save current working area
    TDirectory* currentDir = gDirectory;
    // open histogram file
    TFile* file = new TFile(aInfo->value("time").c_str(), "CREATE");

    for(auto part: pList){
        // compute
        part->ltfPtr->compute();
        const unsigned int nPart = part->ltfPtr->nEvents();
        // print
        std::cout << "n time \t" << nPart << "\n";
        std::cout << "time mean \t" << part->ltfPtr->lifeTime()
                  << "\ntime rms\t" << part->ltfPtr->lifeTimeError()<< std::endl;
        // save TH1F
        part->func->Write();
    }

    // close file and delete pointer
    file->Close();
    delete file;
    currentDir->cd();

    return;
}

void ParticleLifetime::update(const Event &ev){
    static ProperTime* timeRec = ProperTime::instance();
    // loop over particles
    for(auto part: pList){
        // call add function for each MassMean
        // and fill Histogram with invariant mass
        if(part->ltfPtr->add(ev))
            part->func->Fill(timeRec->decayTime());
    }
}

void ParticleLifetime::pCreate(const std::string& name, float min, float max,
                     double minTime, float maxTime, double minScan,
                               double maxScan, double scanStep){
    int nBins = 100;
    // create and store particle
    Particle *p = new Particle;
    p->ltfPtr = new LifetimeFit(min,max, minTime, maxTime, minScan, maxScan, scanStep);
    p->func = new TH1F(&name[0], &name[0], nBins,minTime, maxTime);
    pList.push_back(p);

}
