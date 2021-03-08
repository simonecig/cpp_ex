#include "Event.h"

Event::Event( int id, float x, float y, float z ):
   evNum(id), x(x), y(y), z(z){
  // reserve for the vector 10 elements
  p.reserve(10);
}

Event::~Event() {
  // delete all the particle pointers
  for(unsigned int i=0;i<p.size();i++)
    delete p[i];
}


void Event::add( int charge, float px, float py, float pz ) {

  // check for the number of particles, if maximum reached do nothing
  // and return
  if(p.size() == p.capacity())
    return;

  // create the new particle and fill with data
  Particle *newP = new Particle{charge, px, py, pz};
  // store the new particle pointer in the vector
  p.push_back(newP);

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
  return p.size();
}

// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
  if(i < p.capacity())
    return p[i];
  else return nullptr;
}
