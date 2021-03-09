#include "EventDump.h"
#include "AnalysisFactory.h"
#include "Event.h"
#include <iostream>

using namespace std;

// concrete factory to create an EventDump analyzer
class EventDumpFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "dump" as name for this analyzer and factory
  EventDumpFactory(): AnalysisFactory::AbsFactory("dump") {}
  // create an EventDump when builder is run
  AnalysisSteering* create(const AnalysisInfo* info ) override {
    return new EventDump(info);
  }
};
// create a global EventDumpFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;

EventDump::EventDump(const AnalysisInfo* info):
 AnalysisSteering(info){
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

