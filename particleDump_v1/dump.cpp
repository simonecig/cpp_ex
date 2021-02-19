/* Create a function "dump" taking as argument:
 * - the number of event
 * - the number of particles
 * - 3 floats for the decay point coordinates
 * - an array of integers containing electric charges
 * - 3 arrays of float containing momenta components
 * and printing a dump on the screen .
 * */
#include <iostream>

void dump(const int &evNum, const int &nPart, const float &x,
          const float &y, const float &z, const int *charge,
          const float *px, const float *py, const float *pz){
    std::cout << evNum << std::endl
              << x << ' ' << y << ' ' << z << std::endl
              << nPart << std::endl;
    for(int i  = 0; i < nPart; i++){
      std::cout << charge[i] << ' ' << px[i] << ' '
                << py[i] << ' ' << pz[i] << std::endl;
    }
}
