#ifndef Event_h
#define Event_h

// TODO: unisgned int

class Event {

 public:

    Event( int id, float x, float y, float z ); // create an event with number "n"
                                              // and coordinates x, y, z
    ~Event();

    // composite object Particle to hold all information for each particle
    // ( electric charge and x,y,z momentum components )
    struct Particle {
      int charge;
      float px, py, pz;
    };
    typedef const Particle* part_ptr;

    // add a particle to the event
    void add( int charge, float px, float py, float pz );

    // get event id.
    int eventNumber() const;

    // get decay point coordinates
    float getX() const;
    float getY() const;
    float getZ() const;

    // get number of particles
    int nParticles() const;

    // get particle
    part_ptr particle( unsigned int i ) const;

 private:

  // event-specific informations:
  int evNum; // event id
  float x, y, z; // decay point

  // particles: number and array of pointers
  unsigned int nPart;
  Particle **p;

  // maximum number of particles
  const unsigned int MAXPART = 10;
};

#endif

