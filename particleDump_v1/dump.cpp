/* Create a function ~dump~ to print event data on screen */
#include <iostream>

void dump(int evNum, int nPart, float x, float y, float z,
          int *charge,
          float *px, float *py, float *pz){

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
