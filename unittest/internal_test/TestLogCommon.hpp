// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/*
 * TestLogCommon.hpp
 */

#ifndef TESTLOGCOMMON_HPP
#define TESTLOGCOMMON_HPP

#ifdef RBA_USE_LOG
#include <string>
#include <iostream>
#include <fstream>
#include "RBAILogCollector.hpp"
#include "RBALogManager.hpp"

namespace stub{
class StubLogCollector : public rba::RBAILogCollector
{
 public:
  StubLogCollector(const std::string& expectedLogFilePath, const std::string& outLogFilePath, bool outputs);
   virtual ~StubLogCollector();
   void log(const std::string& logLine) override;
 private:
  std::ofstream writing_file_;
  std::ifstream reading_file_;
  bool outputs_;
};
}
void logOutputForNoReturnBugInit();
void logOutputForNoReturnBug();
#endif

#endif
