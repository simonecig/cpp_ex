#include "EventSource.h"
#include "Event.h"
#include "../util/include/Dispatcher.h"


EventSource::EventSource() {
}


EventSource::~EventSource() {
}


void EventSource::run(){
  const Event* ev;
  // this was taken from ~main~
  while ( ( ev = get() ) != nullptr ) {
    Dispatcher<Event>::notify( *ev );
    delete ev;
  }
  return;
}
