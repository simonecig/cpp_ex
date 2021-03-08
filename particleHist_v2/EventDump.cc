#include "EventDump.h"
#include "Event.h"
#include <iostream>

using namespace std;

EventDump::EventDump() {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::beginJob() {
  return;
}


// function to be called at execution end
void EventDump::endJob() {
  return;
}


// function to be called for each event
void EventDump::process( const Event& ev ) {

  // print the event
  cout << ev.eventNumber() << endl
          << ev.getX() << ' '
          << ev.getY() << ' '
          << ev.getZ() << endl
          << ev.nParticles() << endl;

  // for each particle print its data
  for(unsigned int i=0;i<ev.nParticles();i++){
  cout << ev.particle(i)->charge << ' '
            << ev.particle(i)->px << ' '
            << ev.particle(i)->py << ' '
            << ev.particle(i)->pz << endl;
  }

  return;

}

