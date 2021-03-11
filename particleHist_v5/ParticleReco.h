#ifndef ParticleReco_h
#define ParticleReco_h

#include "Event.h"

#include "../util/include/Singleton.h"
#include "../util/include/LazyObserver.h"

class ParticleReco: public Singleton<ParticleReco>,
                    public LazyObserver<Event> {

  friend class Singleton<ParticleReco>;

 public:

  // particle types
  enum ParticleType { K0, Lambda0, unknown };

  // recompute informations for new event
  void update( const Event& ev ) override;

  // return particle type
  ParticleType getType();
  // return particle energy
  float getEnergy();
  // return particle mass
  float getMass();

 private:

  // private constructor and destructor for singleton
  ParticleReco();
  // deleted copy constructor and assignment to prevent unadvertent copy
  ParticleReco           ( const ParticleReco& x ) = delete;
  ParticleReco& operator=( const ParticleReco& x ) = delete;

  // destructor
  ~ParticleReco() override;

  // particle type
  ParticleType type;
  // particle energy
  float energy;
  // particle mass
  float mass;
};

#endif

