#ifndef LifetimeFit_h
#define LifetimeFit_h

class Event;

class LifetimeFit {

 public:

  LifetimeFit( float min, float max ); // mass range
  ~LifetimeFit();

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  int nEvents() const;  // return number of accepted events

 private:

  const float MINMASS; // min mass
  const float MAXMASS; // max mass

  int acceptedNum; // number of accepted events


};

#endif

