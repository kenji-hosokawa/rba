// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA864_covlog.hpp
 */

#ifndef HA864_COVLOG_HPP
#define HA864_COVLOG_HPP

#ifdef RBA_USE_LOG
#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"
#include "RBAILogCollector.hpp"
#include "RBALogManager.hpp"

#define JSONFILE  "HA864_covlog.json"
#ifndef _MSC_VER
// Linux
#define LOGFILE     "/tmp/HA864_covlog.txt"
#else
// Windows
#define LOGFILE     "./HA864_covlog.txt"
#endif
#ifdef RBA_USE_LOG
namespace
{
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

class MatrixLogCollector : public BaseLogCollector
{
public:
  MatrixLogCollector();
  virtual ~MatrixLogCollector();
  void log(const std::string& logLine);
  bool hasDiffRequest(const std::string & prevLogLine,
		      const std::string & presLogLine);
private:
  std::list<std::string> outputtedLogs;
  std::list<std::string> testCaseList;
  std::list<std::string> previousRequestList;
  std::list<std::string> presentRequestList;
  std::list<std::string> resultList;
  std::list<std::string> cancelRequestList;
};

class HA864_covlog : public ::testing::Test
{
protected:
  HA864_covlog();
  virtual ~HA864_covlog();

  virtual void SetUp();
  virtual void TearDown();

  bool checklog(const std::string& msg, const std::string& expect_str);

protected:
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  rba::RBALogManager* logm_=nullptr;
  MatrixLogCollector* collector_=nullptr;

};

}
#endif
#endif
#endif
