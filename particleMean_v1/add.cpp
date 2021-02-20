#include <cmath>
#include <iostream>
#include "Event.h"


double mass(const Event &ev);

bool add(const Event &ev, float minMass, float maxMass,
         double &sumMass, double &sumSqMass){
    // compute invariant mass of the decay particle
    double invMass = mass(ev);
    // if the the mass is in range, increase the
    // sum of masses and sqaures and return true
    if( (invMass > minMass) && (invMass < maxMass) ){
        sumMass += invMass;
        sumSqMass += pow(invMass,2);
        return true;
    }
    else
        return false;
}
