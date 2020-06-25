// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA588_jsoncheck.hpp
 */

#ifndef HA588_JSONCHECK_HPP
#define HA588_JSONCHECK_HPP

#include <fstream>
#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#ifndef _MSC_VER
// Linux
#define LOGFILE     "/tmp/HA588_stderr.txt"
#else
// Windows
#define LOGFILE     "./HA588_stderr.txt"
#endif

namespace {

class HA588_jsoncheck : public ::testing::Test
{
protected:
  HA588_jsoncheck(void);
  virtual ~HA588_jsoncheck(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  bool checkLog(const std::string& str);

protected:
  std::unique_ptr<std::ofstream> ofs_=nullptr;
  std::streambuf* strbuf_=nullptr;
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;

};

}

#endif
