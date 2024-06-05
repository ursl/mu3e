#ifndef CDBMONGO_h
#define CDBMONGO_h

#include "cdbAbs.hh"

#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>

// ----------------------------------------------------------------------
// implementation class for a Mongo DB
// ----------------------------------------------------------------------

class cdbMongo: public cdbAbs {
public:
  cdbMongo() = default;
  cdbMongo(std::string name, std::string uri, int verbose);
  ~cdbMongo();
  
  void       init();
  runRecord  getRunRecord(int irun) override;
  payload    getPayload(std::string hash) override;
  cfgPayload getConfig(std::string hash) override;
  
  std::vector<std::string>                 readGlobalTags() override;
  std::vector<std::string>                 readTags(std::string gt) override;
  std::map<std::string, std::vector<int> > readIOVs(std::vector<std::string> tags) override;
  
private:
  mongocxx::client   fConn;
  mongocxx::database fDB;
};


#endif
