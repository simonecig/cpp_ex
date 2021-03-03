#include <iostream>
#include <fstream>
#include "Event.h"
#include "MassMean.h"
// TODO: fix RMS
// TODO: doc
Event *read(std::ifstream &file);

int main( int argc, char* argv[] ) {

  // get file name
    const char* fname = argv[1];

    // check if file exists
    std::ifstream file(fname);
    if(!file){
        std::cout << "File not found" << std::endl;
        return 1;
    }

    // create MassMean objects
    MassMean k0(0.495, 0.500);
    MassMean lambda0(1.115, 1.116);

    // loop over events
    const Event* ev;
    while( (ev = read(file)) != nullptr){
      k0.add(*ev);
      lambda0.add(*ev);
      // delete ev;
    }

   // compute results
   k0.compute();
   lambda0.compute();

   // print number of selected events and results for both particles
   std::cout << "K0:\t" << k0.mMean() << "\t"
             << k0.mRMS() << std::endl;
   std::cout << "L0:\t" << lambda0.mMean() << "\t"
             << lambda0.mRMS() << std::endl;
  return 0;

}
