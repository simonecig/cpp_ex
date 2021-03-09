#ifndef __PARTICLEMASS_H_
#define __PARTICLEMASS_H_

#include "AnalysisSteering.h"
#include <vector>
#include <string>

class TH1F;
class MassMean;
class Event;

class ParticleMass: public AnalysisSteering {
    public:
        ParticleMass(const AnalysisInfo* info);
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
        struct Particle{
                std::string name;
                MassMean* mmPtr;
                TH1F *func;
        };

        std::vector<Particle*> pList;

        void pCreate(const std::string& name, float min, float max);

};

#endif // __PARTICLEMASS_H_
