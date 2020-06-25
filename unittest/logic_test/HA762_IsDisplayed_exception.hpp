// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_IsDisplayed_exception.hpp
 */

#ifndef HA762_ISDISPLAYED_EXCEPTION_HPP
#define HA762_ISDISPLAYED_EXCEPTION_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA762_IsDisplayed_exception.json"

namespace {

using namespace rba;

class HA762_IsDisplayed_exception : public ::testing::Test
{
protected:
  HA762_IsDisplayed_exception();
  virtual ~HA762_IsDisplayed_exception();
  virtual void SetUp();
  virtual void TearDown();
  bool isSuccess(const std::string& msg);
  bool isSatisfiedConstraints(const std::string& msg);
  bool isTrue(const std::string& msg, bool res);
  std::string getAllocated(const std::string& msg,
                           const std::string& allocName);
  bool isCanceled(const std::string& msg,
                  const std::string& contentName);
  bool isActive(const std::string& msg,
                const std::string& sceneName);
  int32_t getProperty(const std::string& msg,
                      const std::string& sceneName,
                      const std::string& propertyName);
  bool isEnableAllocatable(const std::string& msg,
                           const std::string& allocName);
  bool isEnableContext(const std::string& msg,
                       const std::string& contextName);
  bool isEnableScene(const std::string& msg,
                     const std::string& sceneName);
  bool isAttenuated(const std::string& msg,
                    const std::string& zoneName);

protected:
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  std::unique_ptr<RBAResult> result_=nullptr;
};

}
#endif
