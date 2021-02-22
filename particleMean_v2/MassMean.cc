#include "MassMean.h"
#include "Event.h"
#include <cmath>
// TODO: check m > 0 before storing value
double mass( const Event& ev );


MassMean::MassMean( float min, float max ):
    MINMASS(min), MAXMASS(max) {}


MassMean::~MassMean() {
}


// add data from a new event
void MassMean::add( const Event& ev ) {

    double m= mass(ev);
    // check for mass being in range
    if( (m >= MINMASS) && (m <= MAXMASS) ){
        // precision limit fix
        m -= MINMASS;
        // update number of events and sums
        acceptedNum++;
        sumM += m;
        sumMsq += pow(m,2);
    }
}


// compute mean and rms
void MassMean::compute() {
    mean = sumM*1./acceptedNum;
    rms = sumMsq*1./acceptedNum - pow(mean,2);
    // add back MINMASS
    mean += MINMASS;
}


// return number of selected events
int MassMean::nEvents() const{ return acceptedNum; }

// return mean and rms
double MassMean::mMean() const{ return mean; }
double MassMean::mRMS() const { return rms; }
