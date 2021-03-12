/*
** Create a function ~read~ to get event data from ~file~.
** The file must contain, for each event:
** - identifier (already stored in ~main~)
** - 3 the decay point coordinates
** - number of particles
** - for each particle:
**   - electric charge
**   - 3 momentum components
** Returns the number of particles
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
