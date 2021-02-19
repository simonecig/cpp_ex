/*
** Create a function "read" taking as arguments
** - the reference to an input file stream
** - the reference to 3 floats to fill with the decay point
**   coordinates
** - an array of integers to fill with electric charges
** - 3 arrays of float to fill with momenta components
** and returning the number of particles
*/
#include <fstream>

int read(std::ifstream &file, float &x, float &y, float &z,
          int *charge, float *px, float *py, float *pz){

    //read the 3 decay point coordinates
    file >> x >> y >> z;

    // read the number of particles
    int nPart = 0;
    file >> nPart;

    //for each particle read the charge and the 3 momentums
    for(int i = 0; i < nPart; i++)
        file >> charge[i] >> px[i] >> py[i] >> pz[i];

    return nPart;
}