// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA729_hierarchy.hpp
 */

#ifndef HA729_HIERARCHY_HPP
#define HA729_HIERARCHY_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"
#include "RBAILogCollector.hpp"
#include "RBALogManager.hpp"

#define JSONFILE  "HA729_hierarchy.json"
#ifndef _MSC_VER
// Linux
#define LOGFILE     "/tmp/HA729_log.txt"
#else
// Windows
#define LOGFILE     "./HA729_log.txt"
#endif

namespace {
#ifdef RBA_USE_LOG
class BaseLogCollector : public rba::RBAILogCollector
{
public:
  BaseLogCollector();
  virtual ~BaseLogCollector();
public:
  bool open(std::string file_path);
  void write(std::string outputLine);
  void close();
protected:
  bool startsWith(const std::string &target, const std::string &keyword);
  std::list<std::string> split(const std::string& line, const char sep);
private:
  std::string model_path;
  std::ofstream ofs;
};

class ConstraintLogCollector : public BaseLogCollector
{
public:
  ConstraintLogCollector();
  virtual ~ConstraintLogCollector();
  void log(const std::string& logLine);
private:
  std::list<std::string> outputtedLogs;
  std::string strHeadString;
  std::string strRuntime;
  bool defValid = false;
  bool expValid;
  bool valid;
  std::string strType;
};
#endif

class HA729_hierarchy : public ::testing::Test {
protected:
  HA729_hierarchy(void);
  virtual ~HA729_hierarchy(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
#ifdef RBA_USE_LOG
  rba::RBALogManager* logm_=nullptr;
  ConstraintLogCollector* collector_=nullptr;
#endif

};

}

#endif
