#include "LifetimeFit.h"
#include "ParticleReco.h"
#include "Event.h"
#include <cmath>

//double mass( const Event& ev );


LifetimeFit::LifetimeFit( float min, float max ):
    MINMASS(min), MAXMASS(max) {}


LifetimeFit::~LifetimeFit() {
}


// add data from a new event
bool LifetimeFit::add( const Event& ev ) {

    static ParticleReco* partRec = ParticleReco::instance();
    double m= partRec->getMass();

    std::cout << "m\t" << m << "\n";
    // check if mass is in range
    if( (m >= MINMASS) && (m <= MAXMASS) ){
        // update number of events and sums
        acceptedNum++;
        return true;
    }
    return false;
}


void LifetimeFit::compute() {}

// return number of selected events
int LifetimeFit::nEvents() const{ return acceptedNum; }
