/*
** Create a "mass" function taking as argument a reference to const-Event
and returning the invariant mass of the decaying particle.
Loop over the particles, and for each one:
- increase the corresponding counter, according to charge,
- increase the 3 momentum components sum,
- compute particle energy for the hypothesis of a decaying K0,
  using the function described above and giving as arguments the 3 momentum
  components and the pion mass,
- compute particle energy for the hypothesis of a decaying Lambda0,
  using the function described above and giving as arguments the 3 momentum
  components and the pion mass for a negative particle or proton mass
  for a positive particle,
- update the total energy sum for both the K0 and Lambda0 hypotheses.
Check the number of positive and negative particles, and return a
negative (unphysical) value if one of the two is different than one.
Compute the invariant mass for both the K0 and Lambda0 hypotheses, and
compute the difference of each one with the known mass of the K0 or Lambda0
respectively. Return the invariant mass for which the corresponding
difference is the smallest.

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
double computeInvM(const float px, const float py, const float pz,
                   const float energy) {
  double ptotSq = pow(px,2) + pow(py,2) + pow(pz,2);
  double msq = pow(energy,2) - ptotSq;
  if(msq > 0)
    return sqrt(msq);
  else
    return -1;
}

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

  // variables for momentum sums
  double pxSum = 0, pySum = 0, pzSum = 0;

  // variables for energy sums, for K0 and Lambda0
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
