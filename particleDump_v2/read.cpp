/*
** Create a function "read" taking as argument an input file
** stream, reading an event and returning a pointer to the event
** or a null pointer.
*/
#include <fstream>
#include "Event.h"

Event *read(std::ifstream &file){
    Event *ev;
    int evNumber = 0;
    // try to read the event id
    if(file >> evNumber)
        ev = new Event; // on success create a new event
    else
        return nullptr; // on fail leave the function

    ev->evNum = evNumber; // store the event number

    // read the point coordinates and the number of particles
    file >> ev->x >> ev->y >> ev->z
         >> ev->nPart;

    //for each particle read the charge and the 3 momentums
    ev->p = new Particle*[ev->nPart];
    for(int i = 0; i < ev->nPart; i++){
        ev->p[i] = new Particle;
        file >> ev->p[i]->charge
             >> ev->p[i]->px
             >> ev->p[i]->py
             >> ev->p[i]->pz;
    }

    return ev;
}
