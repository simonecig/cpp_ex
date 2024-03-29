/*
Loop over the particles, and for each one
compute the invariant mass for both the K0 and
Lambda0 hypotheses
Return the invariant mass closest to the known value.
*/

#include "Event.h"
#include <cmath>

// compute energy from momentum x,y,z components and invariant mass
double computeEnergy(const float px, const float py, const float pz,
                     const double invMass) {
  double psq = pow(px,2) + pow(py,2) + pow(pz,2);
  return sqrt(psq + pow(invMass,2));
}

// compute invariant mass from momentum x,y,z components and energy
double computeInvM(float px, float py, float pz,
                   double energy) {
  double ptotSq = pow(px,2) + pow(py,2) + pow(pz,2);
  double msq = pow(energy,2) - ptotSq;
  if(msq > 0)
    return sqrt(msq);
  else
    return -1;
}

// constants
const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2

double mass(const Event &ev) {
  // retrieve particles in the event
  typedef const Particle* part_ptr;
  const part_ptr* particles = ev.p;

  // variables to loop over particles
  int i = 0, nPart = ev.nPart;
  // positive / negative track counters
  int nPos = 0, nNeg = 0;
  // momentum sums
  double pxSum = 0, pySum = 0, pzSum = 0;
  // energy sums, for K0 and Lambda0
  double enSumK = 0, enSumL = 0;

  // loop over particles
  for(i = 0; i < nPart; i++) {
    // get particle pointer
    const part_ptr particle = particles[i];

    // update momentum sums
    pxSum += particle->px;
    pySum += particle->py;
    pzSum += particle->pz;

    // update energy sums, for K0 and Lambda0 hypotheses
    enSumK += computeEnergy(particle->px, particle->py, particle->pz,
                  massPion);
    if(particle->charge > 0){
      enSumL += computeEnergy(particle->px, particle->py, particle->pz, massProton);
      // update positive track counter
      nPos++;
    }
    else if(particle->charge < 0){
      enSumL += computeEnergy(particle->px, particle->py, particle->pz, massPion);
      // update negative track counter
      nNeg++;
    }
  }

  // check for exactly one positive and one negative track
  if(nPos != 1 || nNeg != 1)
    return -1;

  // invariant masses for different decay product mass hypotheses
  double mK = computeInvM(pxSum, pySum, pzSum, enSumK);
  double mL = computeInvM(pxSum, pySum, pzSum, enSumL);

  // compare invariant masses with known values and return the nearest one
  if( std::abs((mK - massK0)) < std::abs((mL - massLambda0)) )
    return mK;
  else if( std::abs((mL - massLambda0)) < std::abs((mK - massK0)) )
    return mL;
  else
    return -2;
}
