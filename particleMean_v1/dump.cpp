/* Create a function ~dump~ to print event data on screen */

#include <iostream>
#include "Event.h"

void dump(const Event &ev){
    // print event data on screen
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
