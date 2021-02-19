/*
** Create a function "clear" deleting the event and its content, including
** all the particles.
*/
#include "Event.h"
#include "Particle.h"

void clear(const Event *ev){
    // delete all the Particle structs
    for(int i = 0; i < ev->nPart; i++)
        delete ev->p[i];
    // delete the array of pointers
    delete[] ev->p;
    // delete the Event struct
    delete ev;
}
