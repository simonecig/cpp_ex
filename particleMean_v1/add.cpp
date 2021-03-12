/*
**  Compute inveriant mass of the decay particle
**  Check if it's in range (if not return false)
**  Update sums
**  Return true
*/
#include <cmath>
#include "Event.h"


double mass(const Event &ev);

bool add(const Event &ev, float minMass, float maxMass,
         double &sumMass, double &sumSqMass){

    // compute invariant mass of the decay particle
    double invMass = mass(ev);

    // chech if mass is in range
    if( (invMass >= minMass) && (invMass <= maxMass) ){
        // limited precision fix
        invMass -= minMass;
        // update sums
        sumMass += invMass;
        sumSqMass += pow(invMass,2);
        return true;
    }
    return false;
}
