#include "Event.h"

Event::Event( int id, float x, float y, float z ):
   evNum(id), x(x), y(y), z(z){
  // allocate a buffer for particle pointers
  p = new Particle*[MAXPART];
}

Event::~Event() {
  // delete all the particle pointers
  for(unsigned int i=0;i<MAXPART;i++)
    delete p[i];
  // delete the pointers array
  delete[] p;
}


void Event::add( int charge, float px, float py, float pz ) {

  // check for the number of particles, if maximum reached do nothing
  // and return
  if(nPart == MAXPART)
    return;

  // create the new particle and fill with data
  Particle *newP = new Particle{charge, px, py, pz};
  // store the new particle pointer in the array and increase counter
  p[nPart] = newP;
  nPart++;

  return;

}


// get event id.
int Event::eventNumber() const {
  return evNum;
}


// get decay point coordinates
float Event::getX() const{
  return x;
}
float Event::getY() const{
  return y;
}
float Event::getZ() const{
  return z;
}

// get number of particles
unsigned int Event::nParticles() const{
  return nPart;
}

// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
  if(i < MAXPART)
    return p[i];
  else return nullptr;
}
