#include "payload.hh"
#include "base64.hh"

#include <iostream>
#include <sstream>

using namespace std;


// ----------------------------------------------------------------------
payload::payload() : fLength(0),
                     fComment("now what?"), fHash("tag_X_iov_Y"), 
                     fBLOB(std::string("empty payload")) {

};


// ----------------------------------------------------------------------
void payload::print() {
  cout << printString() << endl;
}


// ----------------------------------------------------------------------
string payload::printString() {
  std::stringstream sstr;
  sstr << "/**/hash ->" << fHash
       << "<- /**/comment ->" << fComment
       << "<- /**/BLOB ->" << fBLOB
       << "<-";
  return sstr.str();
}


// ----------------------------------------------------------------------
string payload::json() {
  std::stringstream sstr;
  sstr << "{\"hash\" : \"" << fHash << "\", "
       << "\"comment\" : \"" << fComment << "\","
       << "\"BLOB\" : \"" << base64_encode(fBLOB) << "\"}";
  return sstr.str();
}
