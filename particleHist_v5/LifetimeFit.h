#ifndef LifetimeFit_h
#define LifetimeFit_h
#include <vector>
class Event;

class LifetimeFit {

 public:

    LifetimeFit( float min, float max, double minTime, double maxTime,
                double minScan, double maxScan, double scanStep); // mass range
    ~LifetimeFit();

    bool add( const Event& ev );      // add data from a new event
    void compute();                   // compute mean and rms

    int nEvents() const;  // return number of accepted events

    double lifeTime() const;
    double lifeTimeError() const;

 private:

    const float MINMASS; // min mass
    const float MAXMASS; // max mass

    //int acceptedNum; // number of accepted events

    double minTime, maxTime;
    double minScan, maxScan, scanStep;

    double mean, rms;
    std::vector<double> decayTimes;

};

#endif

