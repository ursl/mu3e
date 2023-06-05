#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>

#include "cdbAscii.hh"
#include "cdbMongo.hh"
#include "cdbJSON.hh"
#include "CdbClassFactory.hh"

#include "calPixel.hh"


using namespace std;

void printStuff(cdb*);
void aFewRuns(cdb*, string globalTag, calAbs *);

// ----------------------------------------------------------------------
// testCDB
// -------
//
// Examples:
// bin/testCDB -gt dt23prompt -m 1 -r 1000
// bin/testCDB -gt dt23intrun
// bin/testCDB -gt dt23intrun -v 10
// 
// ----------------------------------------------------------------------




// ----------------------------------------------------------------------
int main(int argc, char* argv[]) {
  
  // -- command line arguments
  int mode(0), run(0), verbose(0);
  string db("ascii"), gt("dt23intrun");
  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i], "-db"))  {db = string(argv[++i]);}
    if (!strcmp(argv[i], "-gt"))  {gt = string(argv[++i]);}
    if (!strcmp(argv[i], "-m"))   {mode = atoi(argv[++i]);}
    if (!strcmp(argv[i], "-r"))   {run = atoi(argv[++i]);}
    if (!strcmp(argv[i], "-v"))   {verbose = atoi(argv[++i]);}
  }

  cdb *pDB(0);
  if (string::npos != db.find("ascii")) {
    pDB = new cdbAscii(gt, "ascii");
    if (verbose > 0) pDB->setVerbosity(verbose);
  } else if (string::npos != db.find("json")) {
    pDB = new cdbJSON(gt, "ascii");
    if (verbose > 0) pDB->setVerbosity(verbose);
    return 0;
  } else if (string::npos != db.find("mongo")) {
    string ms("mongodb://127.0.0.1:27017/?directConnection=true&serverSelectionTimeoutMS=2000&appName=mongosh+1.7.1");
    pDB = new cdbMongo(gt, ms);
    if (verbose > 0) pDB->setVerbosity(verbose);
  } else {
    cout << "ERROR: " << db << " not known." << endl;
    return 0;
  }
  
  // -- calibration classes instantiation and registration must happen before setting the run number in the CBD
  CdbClassFactory *cdbcf = CdbClassFactory::instance(pDB);
  if (verbose > 0) cdbcf->setVerbosity(verbose);

  calAbs *cal0 = cdbcf->createClass("calPixel", "pixel_ir");
    
  pDB->setRunNumber(3);
  cout << "set run number to " << pDB->getRunNumber() << endl;

  
  if (0 == mode) {
    cout << "----------------------------------------------------------------------" << endl;
    printStuff(pDB);
    cout << "----------------------------------------------------------------------" << endl;
  } else if (1 == mode) {
    cout << "run = " << pDB->getRunNumber() << " payload hash -> " << cal0->getHash() << "<-" << endl;
  } else if (2 == mode) {
    aFewRuns(pDB, gt, cal0);  
  }
  return 0;
}


// ----------------------------------------------------------------------
void printStuff(cdb *db) {
  vector<string> gt = db->getGlobalTags();
  for (auto igt : gt) {
    cout << "GT " << igt << endl;
    vector<string> tags = db->getTags(igt);
    for (auto itt : tags) {
      cout << " tag: " << itt << endl;
      vector<int> iovs = db->getIOVs(itt);
      for (auto ittt :  iovs) {
        cout << "   iov " << ittt << endl;
      }
    }
  }
  
  string pl = db->getPayload(12, "pixel_ir");
  cout << "printStuff> pixel payload: " << pl << endl;
}


// ----------------------------------------------------------------------
void aFewRuns(cdb *db, string gt, calAbs *cal) {
  cout << "DB " << db->getGlobalTag() << endl;
  vector<int> vruns{23,24,25,56,90,156,157,201,202};
  for (auto it: vruns) {
    db->setRunNumber(it);
    cout << "now for run = " << it << " payload hash ->" << cal->getHash() << "<-" << endl;
  }   
}
    
  
