#include "LifetimeFit.h"
#include "ParticleReco.h"
#include "ProperTime.h"
#include "../AnalysisFramework/Event.h"
#include "../AnalysisUtilities/QuadraticFitter.h"
#include <cmath>

//double mass( const Event& ev );


LifetimeFit::LifetimeFit(float min, float max, double minTime,
                         double maxTime, double minScan,
                         double maxScan, double scanStep):
    MINMASS(min), MAXMASS(max),
    minTime(minTime), maxTime(maxTime),
    minScan(minScan), maxScan(maxScan), scanStep(scanStep){}


LifetimeFit::~LifetimeFit() {
}


// add data from a new event
bool LifetimeFit::add( const Event& ev ) {

    static ParticleReco* partRec = ParticleReco::instance();
    static ProperTime* prpTime = ProperTime::instance();
    double m = partRec->getMass();
    double time = prpTime->decayTime();
    // check if mass is in range
    if( m>=MINMASS && m <= MAXMASS)
        // check if time is in range
        if(time>= minTime && time<=maxTime){
            // store the decay time
            decayTimes.push_back(time);
            return true;
        }

    return false;
}

double LifetimeFit::lifeTime() const{ return mean; }
double LifetimeFit::lifeTimeError() const{ return rms; }

// return number of selected events
int LifetimeFit::nEvents() const{ return decayTimes.size(); }

void LifetimeFit::compute() {
    QuadraticFitter qFit;
    for(double t_s = minScan; t_s < maxScan; t_s += scanStep){
        // compute L(t_s)
        double L = 0;
        for(double t_i: decayTimes)
            L+= ( (t_i/t_s) + log(t_s) + log(exp(-minTime/t_s) - exp(-maxTime/t_s)) );
        qFit.add(t_s,L);
    }
    mean = - qFit.b() / (2. * qFit.c());
    rms = 1./sqrt(2. * qFit.c());
}
