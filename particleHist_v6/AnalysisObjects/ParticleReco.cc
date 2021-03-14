#include "ParticleReco.h"
#include "../AnalysisFramework/Event.h"
#include "../AnalysisUtilities/Utilities.h"
#include "../AnalysisUtilities/Constants.h"
#include <iostream>
#include <cmath>

using namespace std;


// constructor
ParticleReco::ParticleReco() {
}


// destructor
ParticleReco::~ParticleReco() {
}


// recompute tag informations for new event
void ParticleReco::update( const Event& ev ) {

  // set default quantities
  type   = unknown;
  energy = -1.0;
  mass   = -1.0;

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products

  // retrieve particles in the event
  typedef const Event::Particle* part_ptr;

  // variables to loop over particles
  unsigned int i = 0, nPart = ev.nParticles();
  // positive / negative track counters
  unsigned int nPos = 0, nNeg = 0;
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
  if(nPos == 1 && nNeg == 1){
    // invariant masses for different decay product mass hypotheses
    double mK = Utilities::computeM(pxSum, pySum, pzSum, enSumK);
    double mL = Utilities::computeM(pxSum, pySum, pzSum, enSumL);

  // compare invariant masses with known values and set final values
  // ( type, energy and mass )
  if( std::abs((mK - Constants::massK0)) < std::abs((mL - Constants::massLambda0)) ){
     type = K0;
     mass = mK;
     energy = enSumK;
   }
  else if( std::abs((mL - Constants::massLambda0)) < std::abs((mK - Constants::massK0)) ){
    type = Lambda0;
    mass = mL;
    energy = enSumL;
  }
  }

  return;

}


// return particle type
ParticleReco::ParticleType ParticleReco::getType() {
  // check for new event and return result
  check();
  return type;
}


// return particle energy
float ParticleReco::getEnergy() {
  // check for new event and return result
  check();
  return energy;
}


// return particle mass
float ParticleReco::getMass() {
  // check for new event and return result
  check();
  return mass;
}
