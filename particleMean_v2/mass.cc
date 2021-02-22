/*
 */

#include "Utilities.h"
#include "Constants.h"
#include "Event.h"
#include <cmath>

double mass(const Event &ev) {

  // retrieve particles in the event
  typedef const Event::Particle* part_ptr;

  // variables to loop over particles
  int i = 0, nPart = ev.nParticles();

  // positive / negative track counters
  int nPos = 0, nNeg = 0;

  // variables for momentum sums
  double pxSum = 0, pySum = 0, pzSum = 0;

  // variables for energy sums, for K0 and Lambda0
  double enSumK = 0, enSumL = 0;

  // loop over particles
  for(i = 0; i < nPart; i++) {
    // get particle pointer
    const part_ptr particle = ev.particle(i);

    // update momentum sums
    pxSum += particle->px;
    pySum += particle->py;
    pzSum += particle->pz;

    // update energy sums, for K0 and Lambda0 hypotheses
    enSumK += Utilities::computeEnergy(particle->px, particle->py,
                                       particle->pz, Constants::massPion);
    if(particle->charge > 0){
      enSumL += Utilities::computeEnergy(particle->px, particle->py,
                                         particle->pz, Constants::massProton);
      // update positive track counter
      nPos++;
    }
    else if(particle->charge < 0){
      enSumL += Utilities::computeEnergy(particle->px, particle->py,
                                         particle->pz, Constants::massPion);
      // update negative track counter
      nNeg++;
    }
  }

  // check for exactly one positive and one negative track
  if(nPos != 1 || nNeg != 1)
    return -1;

  // invariant masses for different decay product mass hypotheses
  double mK = Utilities::computeM(pxSum, pySum, pzSum, enSumK);
  double mL = Utilities::computeM(pxSum, pySum, pzSum, enSumL);

  // compare invariant masses with known values and return the nearest one
  if( std::abs((mK - Constants::massK0)) < std::abs((mL - Constants::massLambda0)) )
    return mK;
  else if( std::abs((mL - Constants::massLambda0)) < std::abs((mK - Constants::massK0)) )
    return mL;
  else
    return -2;
}
