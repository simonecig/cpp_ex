/*
** Create a ~main~ function taking the file name from the
** command string, opening the file, reading the events
** and dumping them on the screen.
*/

#include <iostream>
#include <fstream>

int read(std::ifstream &file, float &x, float &y, float &z,
          int *charge, float *px, float *py, float *pz);

void dump(int evNum, int nPart, float x, float y, float z,
          int *charge,
          float *px, float *py, float *pz);

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
