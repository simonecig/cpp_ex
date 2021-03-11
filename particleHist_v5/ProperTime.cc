#include "ProperTime.h"
#include "ParticleReco.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

using namespace std;


// constructor
ProperTime::ProperTime() {
}


// destructor
ProperTime::~ProperTime() {
}


// recompute tag informations for new event
void ProperTime::update( const Event& ev ) {
  // set default quantity
  time   = -1.0;

  static ParticleReco* partRec = ParticleReco::instance();
  const double m = partRec->getMass();
  const double e = partRec->getEnergy();
  const float x = ev.getX(),
    y = ev.getY(),
    z = ev.getZ();
  double p = sqrt(e*e-m*m);
  double d = sqrt(x*x+y*y+z*z);
  time=d*m/(p*Constants::lightVelocity);
  std::cout << "p\t" << p << std::endl;
  return;

}

// return time
float ProperTime::decayTime(){
  // check for new event and return result
  check();
  return time;
}
