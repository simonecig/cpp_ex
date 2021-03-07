#include "EventReadFromFile.h"

#include "Event.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name ) {
  file = new ifstream( name.c_str(), ios::binary );
}


EventReadFromFile::~EventReadFromFile() {
  delete file;
}


// get an event
const Event* EventReadFromFile::get() {
  return readFile();
}


// read an event
const Event* EventReadFromFile::readFile() {
  Event *ev;
  int evNumber=0;
  unsigned int nPart=0;
  float x=0, y=0, z=0;
  // try to read the event id
  if(!(*file >> evNumber))
      return nullptr; // on fail leave the function

  // read the point coordinates and the number of particles
  *file >> x >> y >> z >> nPart;
  ev = new Event(evNumber, x, y, z);
  //for each particle read the charge and the 3 momentums
  for(unsigned int i=0;i<nPart;i++){
      int charge=0;
      float px=0,py=0,pz=0;
      *file >> charge
           >> px >> py >> pz;
      ev->add(charge, px, py, pz);
  }

  return ev;
}
