#include "Utilities.h"
#include "cmath"

// compute invariant mass from momentum x,y,z components and energy
double Utilities::computeM(float px, float py, float pz, double energy) {
  double ptotSq = pow(px,2) + pow(py,2) + pow(pz,2);
  double msq = pow(energy,2) - ptotSq;
  if(msq > 0)
    return sqrt(msq);
  else
    return -1;
}

// compute energy from momentum x,y,z components and invariant mass
double Utilities::computeEnergy(float px, float py, float pz, double invMass) {
  double psq = pow(px,2) + pow(py,2) + pow(pz,2);
  return sqrt(psq + pow(invMass,2));
}
