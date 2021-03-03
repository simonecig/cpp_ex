/* Create a function "dump" taking as argument a reference to
 * const-event and printing a dump on the screen
 * */

#include <iostream>
#include "Event.h"

void dump(const Event &ev){
    // print the event
    std::cout << ev.eventNumber() << std::endl
              << ev.getX() << ' '
              << ev.getY() << ' '
              << ev.getZ() << std::endl
              << ev.nParticles() << std::endl;
    // for each particle print its data
    for(unsigned int i=0;i<ev.nParticles();i++){
      std::cout << ev.particle(i)->charge << ' '
                << ev.particle(i)->px << ' '
                << ev.particle(i)->py << ' '
                << ev.particle(i)->pz << std::endl;
    }
}
