#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <dirent.h>  /// for directory reading

#include <chrono>

#include "cdbUtil.hh"
#include "base64.hh"

#include "calPixelAlignment.hh"
#include "calFibreAlignment.hh"
#include "calMppcAlignment.hh"
#include "calTileAlignment.hh"
#include "calPixelCablingMap.hh"
#include "calPixelQuality.hh"

#include "calFibreAlignment.hh"


using namespace std;

// ----------------------------------------------------------------------
// cdbPrintPayload /path/to/payload
// ---------------
//
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------=
int main(int argc, char* argv[]) {

  string filename(""), pdir(""), hash("");
  
  // -- command line arguments
  if (argc < 2) {
    cout << "provide a payload file" << endl;
    return 0; 
  } else {
    filename = argv[1]; 
  }

  pdir = filename.substr(0, filename.find_last_of("/")+1);
  hash = filename.substr(filename.find_last_of("/")+1);
  cout << "payload ->" << filename  << "<-" << endl
       << "dir ->" << pdir << "<-" << endl
       << "hash ->" << hash << "<-" << endl;

  calAbs *c(0); 
  if (string::npos != filename.find("pixelalignment")) {
    c = new calPixelAlignment();
    c->readPayloadFromFile(hash, pdir);
    cout << "hash:    " << c->getPayload(hash).fHash << endl;
    cout << "comment: " << c->getPayload(hash).fComment << endl;
    cout << "schema:  " << c->getPayload(hash).fSchema << endl;
    cout << "date:    " << c->getPayload(hash).fDate << endl;
    c->printBLOB(c->getPayload(hash).fBLOB);
  } else if (string::npos != filename.find("fibrealignment")) {
    c = new calFibreAlignment();
    c->readPayloadFromFile(hash, pdir);
    c->printBLOB(c->getPayload(hash).fBLOB);
  } else if (string::npos != filename.find("mppcalignment")) {
    c = new calMppcAlignment();
    c->readPayloadFromFile(hash, pdir);
    c->printBLOB(c->getPayload(hash).fBLOB);
  } else if (string::npos != filename.find("tilealignment")) {
    c = new calTileAlignment();
    c->readPayloadFromFile(hash, pdir);
    c->printBLOB(c->getPayload(hash).fBLOB);
  } else if (string::npos != filename.find("pixelquality")) {
    c = new calPixelQuality();
    c->readPayloadFromFile(hash, pdir);
    c->printBLOB(c->getPayload(hash).fBLOB);
  } else if (string::npos != filename.find("pixelcabling")) {
    c = new calPixelCablingMap();
    c->readPayloadFromFile(hash, pdir);
    c->printBLOB(c->getPayload(hash).fBLOB);

  } 

  
  return 0; 
}
