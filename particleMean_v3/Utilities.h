/*
 * Compute the energy or the mass from the 3
 * momentum components and the mass/energy.
 *  */
#ifndef __UTILITIES_H_
#define __UTILITIES_H_

class Utilities{
    public:
        static double computeEnergy(float px, float py, float pz,
                                    double invMass);
        static double computeM(float px, float py, float pz,
                               double energy);
};

#endif // __UTILITIES_H_
