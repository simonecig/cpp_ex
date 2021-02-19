/*
** Create an "Event" struct with members corresponding to the
** data for each event (event identifier, 3 decay point coordinates,
** number of particles, array of pointers to Particle structs).
*/
#ifndef EVENT_H_
#define EVENT_H_

struct Particle;

struct Event{
  // event variables
    int evNum;
    float x, y,z;
    int nPart;
    Particle **p;
};


#endif // EVENT_H
