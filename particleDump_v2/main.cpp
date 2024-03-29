#include <iostream>
#include <fstream>
#include "Event.h"

struct Event;
struct Particle;

Event* read(std::ifstream &file);
void dump(const Event &ev);
void clear(const Event *ev);

int main(int argc, char *argv[]) {
    // get file name
    const char* fname = argv[1];

    // check if file exists
    std::ifstream file(fname);
    if(!file){
        std::cout << "File not found" << std::endl;
        return 1;
    }

    // loop over events
    Event* ev;
    while( (ev = read(file)) != nullptr ){
        dump(*ev);
        clear(ev);
    }

    return 0;
}
