/*
** Class to compute statistics
 */

#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean {

 public:

  MassMean( float min, float max ); // mass range
  ~MassMean();

  void add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  int nEvents() const;  // return number of accepted events
  double mMean() const; // return mean mass
  double mRMS() const;  // return rms  mass

 private:

  const float MINMASS; // min mass
  const float MAXMASS; // max mass

  int acceptedNum; // number of accepted events
  double sumM; // sum of masses
  double sumMsq; // sum of masses square

  double mean; // mean mass
  double rms; // rms  mass

};

#endif

