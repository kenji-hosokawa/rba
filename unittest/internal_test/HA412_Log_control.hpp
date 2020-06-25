// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA412_Log_control.hpp
 */

#ifndef HA412_LOG_CONTROLL_HPP
#define HA412_LOG_CONTROLL_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"
#include "RBAILogCollector.hpp"
#include "RBALogManager.hpp"

#define JSONFILE  "HA412_Log_control.json"

#ifndef _MSC_VER
// Linux
#define LOGFILE	    "/tmp/HA412_Log_control.txt"
#else
// Windows
#define LOGFILE	    "./HA412_Log_control.txt"
#endif

namespace
{
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
  bool defValid;
  bool expValid;
  bool valid;
  std::string strType;
};
#endif
class HA412_Log_control : public ::testing::Test
{
protected:
  HA412_Log_control();
  virtual ~HA412_Log_control();

#ifdef RBA_USE_LOG
  virtual void SetUp();
  virtual void TearDown();

protected:
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  rba::RBALogManager* logm_=nullptr;
  ConstraintLogCollector* collector_=nullptr;
#endif
};
}

#endif
