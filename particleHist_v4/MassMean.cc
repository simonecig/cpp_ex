#include "MassMean.h"
#include "ParticleReco.h"
#include "Event.h"
#include <cmath>

//double mass( const Event& ev );


MassMean::MassMean( float min, float max ):
    MINMASS(min), MAXMASS(max) {}


MassMean::~MassMean() {
}


// add data from a new event
bool MassMean::add( const Event& ev ) {

    static ParticleReco* partRec = ParticleReco::instance();
    double m= partRec->getMass();

    // check if mass is in range
    if( (m >= MINMASS) && (m <= MAXMASS) ){
        // precision limit fix
        m -= MINMASS;
        // update number of events and sums
        acceptedNum++;
        sumM += m;
        sumMsq += pow(m,2);
        return true;
    }
    return false;
}


// compute mean and rms
void MassMean::compute() {
    mean = sumM*1./acceptedNum;
    rms = sqrt( sumMsq*1./acceptedNum - pow(mean,2) );
    // add back MINMASS
    mean += MINMASS;
}

// return number of selected events
int MassMean::nEvents() const{ return acceptedNum; }

// return mean and rms
double MassMean::mMean() const{ return mean; }
double MassMean::mRMS() const { return rms; }
