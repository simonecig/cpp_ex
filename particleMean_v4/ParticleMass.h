#ifndef __PARTICLEMASS_H_
#define __PARTICLEMASS_H_

#include "AnalysisSteering.h"
#include <vector>

class MassMean;
class Event;
class ParticleMass: public AnalysisSteering {
    public:
        ParticleMass();
        // delete copy constructor and assignment
        // to prevent unadvertent copy
        ParticleMass(const ParticleMass &x) = delete;
        ParticleMass& operator=(const ParticleMass &x) = delete;

        ~ParticleMass() override;

        // function to be called at execution start
        void beginJob() override;
        // function to be called at execution end
        void endJob() override;
        // function to be called for each event
        void process(const Event &ev) override;

    private:
        std::vector<MassMean*> pList;

};

#endif // __PARTICLEMASS_H_
