/*
** Create a "main" function taking the file name from the
** command string, opening the file and calling the read
** and dump functions.
** Dimension the arrays in the "main" using 10 as max number
** of particles.
** For each event try to read the event identifier in the
** main and on success call the read function to read
** the other data and then call the "dump" function.
**
*/

#include <iostream>
#include <fstream>

int read(std::ifstream &file, float &x, float &y, float &z,
          int *charge, float *px, float *py, float *pz);

void dump(const int &evNum, const int &nPart, const float &x,
          const float &y, const float &z, const int *charge,
          const float *px, const float *py, const float *pz);

int main(int argc, char *argv[]) {
    const char* fname = argv[1];

    // event variables
    int evNum = 0;
    float x = 0, y = 0, z = 0;
    int nPart = 0;
    int charge[10];
    float px[10], py[10], pz[10];

    // check if file exists
    std::ifstream file(fname);
    if(!file){
        std::cout << "File not found" << std::endl;
        return 1;
    }

    // loop over events
    while(file >> evNum){
        nPart=read(file, x, y, z, charge, px, py, pz);
        dump(evNum, nPart, x, y, z, charge, px, py, pz);
    }

    return 0;
}
