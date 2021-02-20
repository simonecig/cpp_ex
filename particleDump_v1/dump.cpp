/* Create a function "dump" taking as argument:
 * - the number of event
 * - the number of particles
 * - 3 floats for the decay point coordinates
 * - an array of integers containing electric charges
 * - 3 arrays of float containing momenta components
 * and printing a dump on the screen .
 * */
#include <iostream>

void dump(int evNum, int nPart, float x, float y, float z,
          const int *charge,
          const float *px, const float *py, const float *pz){

  // print event data on screen
  std::cout << evNum << std::endl
            << x << ' ' << y << ' ' << z << std::endl
            << nPart << std::endl;

  //loop over the particles
  for(int i  = 0; i < nPart; i++){
    std::cout << charge[i] << ' ' << px[i] << ' '
              << py[i] << ' ' << pz[i] << std::endl;
  }
}
