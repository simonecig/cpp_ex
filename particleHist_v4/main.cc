#include <vector>
#include <string>
#include <sstream>

#include "Event.h"
#include "SourceFactory.h"
#include "EventSource.h"
#include "AnalysisInfo.h"
#include "AnalysisSteering.h"
#include "AnalysisFactory.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

  // store command line parameters
  AnalysisInfo* info = new AnalysisInfo( argc, argv );

  // create data source
  EventSource* es = SourceFactory::create( info );

  // create a list of analyzers
  vector<AnalysisSteering*> aList = AnalysisFactory::create(info);

  // initialize all analyzers
  for ( auto as: aList )
    as->beginJob();

  // loop over events
  es->run();

  // finalize all analyzers
  for ( auto as: aList )
    as->endJob();

  return 0;

}
