/* Create a function "dump" taking as argument a reference to
 * const-event and printing a dump on the screen
 * */

#include <iostream>
#include "Event.h"
//#include "Particle.h"

void dump(const Event &ev){
    // print the event
    std::cout << ev.evNum << std::endl
              << ev.x << ' ' << ev.y << ' ' << ev.z << std::endl
              << ev.nPart << std::endl;
    // for each particle print its data
    for(int i  = 0; i < ev.nPart; i++){
      std::cout << ev.p[i]->charge << ' '
                << ev.p[i]->px << ' '
                << ev.p[i]->py << ' '
                << ev.p[i]->pz << std::endl;
    }
}
