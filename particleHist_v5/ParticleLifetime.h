#ifndef __PARTICLEMASS_H_
#define __PARTICLEMASS_H_

#include "AnalysisSteering.h"
#include "../util/include/ActiveObserver.h"
#include <vector>
#include <string>

class TH1F;
class LifetimeFit;
class Event;

class ParticleLifetime: public AnalysisSteering,
                    public ActiveObserver<Event>{
    public:
        ParticleLifetime(const AnalysisInfo* info);
        // delete copy constructor and assignment
        // to prevent unadvertent copy
        ParticleLifetime(const ParticleLifetime &x) = delete;
        ParticleLifetime& operator=(const ParticleLifetime &x) = delete;

        ~ParticleLifetime() override;

        // function to be called at execution start
        void beginJob() override;
        // function to be called at execution end
        void endJob() override;
        // function to be called for each event
        void update(const Event &ev) override;

    private:
        struct Particle{
                std::string name;
                LifetimeFit* ltfPtr;
                TH1F *func;
        };

        std::vector<Particle*> pList;

        void pCreate(const std::string& name, float min, float max,
                             float timeMin, float timeMax);

};

#endif // __PARTICLEMASS_H_
