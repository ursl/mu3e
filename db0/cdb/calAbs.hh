#ifndef CALABS_h
#define CALABS_h

#include "cdb.hh"

#include <string>
#include <vector>
#include <map>

// ----------------------------------------------------------------------
// abstract base class for calibration classes
// ----------------------------------------------------------------------

class calAbs {
public:
  calAbs() = default;
  calAbs(cdb *db);
  calAbs(cdb *db, std::string gt);
  calAbs(cdb *db, std::string gt, std::string tag);
  ~calAbs();

  std::string        getPayload(int irun);
  
protected: 
	cdb                                *fDB;
  std::string                        fGlobalTag;
  std::string                        fTag;
  std::map<std::string, std::string> fTagIovPayloadMap;  // cache
};


#endif
