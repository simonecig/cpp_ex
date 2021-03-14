#include "ParticleMass.h"
#include "../AnalysisUtilities/Constants.h"
#include "../AnalysisObjects/MassMean.h"
#include "../AnalysisFramework/Event.h"
#include "TFile.h"
#include "TH1F.h"
#include "../AnalysisFramework/AnalysisFactory.h"
#include "../AnalysisFramework/AnalysisInfo.h"
#include "../AnalysisObjects/ParticleReco.h"
#include "util/include/TFileProxy.h"
#include <fstream>
#include <iostream>

// concrete factory to create a ParticleMass analyzer
class ParticleMassFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleMassFactory(): AnalysisFactory::AbsFactory( "mass" ) {}
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
    std::ifstream file(aInfo->value("mranges").c_str());
    // read from file
    std::string name;
    float eMin;
    float eMax;
    while (file >> name >> eMin >> eMax){
       pCreate("mass"+name,eMin,eMax);
    }
    return;
}

void ParticleMass::endJob(){

    // save current working area
    TDirectory* currentDir = gDirectory;

    std::string fname = "histo.root";
    // check if user has defined a name
    if(aInfo->contains("plot")) fname = aInfo->value("plot");
    // open histogram file
    TFileProxy* file = new TFileProxy(fname.c_str(), "CREATE");

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
    // get number of bins
    int nBins=100;
    // check for user specified value
    if(aInfo->contains("nbins")){
        // try to convert string to int
        try{
            int choice = std::stoi(aInfo->value("nbins"));
            // if choice is negative throw the invalid_argument exception
            if(choice > 0) nBins = choice;
            else throw(std::invalid_argument("negativeValue"));

        }
        // on fail keep the default value
        catch (std::invalid_argument &e){
            std::cout << "nBins invalid. Using " << nBins
                      << " instead." << std::endl;
            // change "nbins" value to prevent multiple throws
            aInfo->setValue("nbins",std::to_string(nBins));
        }
    }
    // create and store particle
    Particle *p = new Particle;
    p->mmPtr = new MassMean(min,max);
    p->func = new TH1F(&name[0], &name[0], nBins,min, max);
    pList.push_back(p);

}
