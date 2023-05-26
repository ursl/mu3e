#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>

#include "cdbAscii.hh"
#include "cdbMongo.hh"


using namespace std;

// ----------------------------------------------------------------------
int main(int argc, char* argv[]) {
    
  // -- command line arguments
  int nruns(-1);
  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i],"-n"))  {nruns   = atoi(argv[++i]);}
  }

  cdb *db = new cdb();
  cout << "instantiated cdb with name " << db->getName() << endl;

  cdb *db0 = new cdb("abstract", "nowhere");
  cout << "instantiated cdb with name " << db0->getName() << endl;

  if (1) {
    cdb *db1 = new cdbAscii("ascii", "ascii");
    cout << "instantiated cdbAscii with name " << db1->getName() << endl;
    vector<string> gt = db1->getGlobalTags();
    for (auto igt : gt) {
      cout << "GT " << igt << endl;
      vector<string> tags = db1->getTags(igt);
      for (auto itt : tags) {
        cout << " tag: " << itt << endl;
        vector<int> iovs = db1->getIovs(itt);
        for (auto ittt :  iovs) {
          cout << "   iov " << ittt << endl;
        }
      }
    }

    string pl = db1->getPayload(12, "pixelir");
    cout << "pixel payload: " << pl << endl;

  }

  cout << "----------------------------------------------------------------------" << endl;
  
  if (1) {
    
    string ms("mongodb://127.0.0.1:27017/?directConnection=true&serverSelectionTimeoutMS=2000&appName=mongosh+1.7.1");
    cdb *md1 = new cdbMongo("mongo", ms);
    cout << "instantiated cdbMongo with name " << md1->getName() << endl;
    vector<string> gt = md1->getGlobalTags();
    for (auto igt : gt) {
      cout << "GT " << igt << endl;
      vector<string> tags = md1->getTags(igt);
      for (auto itt : tags) {
        cout << " tag: " << itt << endl;
        vector<int> iovs = md1->getIovs(itt);
        for (auto ittt :  iovs) {
          cout << "   iov " << ittt << endl;
        }
      }
    }

    string pl = md1->getPayload(12, "pixelir");
    cout << "pixel payload: " << pl << endl;
  }
  
  return 0;
}
