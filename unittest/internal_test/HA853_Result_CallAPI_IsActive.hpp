// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA853_Result_CallAPI_IsActive.hpp
 */

#ifndef HA853_RESULT_CALLAPI_ISACTIVE_HPP
#define HA853_RESULT_CALLAPI_ISACTIVE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "HA853_Result_CallAPI_IsActive.json"

namespace {

using namespace rba;

class HA853_Result_CallAPI_IsActive : public ::testing::Test
{
protected:
  HA853_Result_CallAPI_IsActive();
  virtual ~HA853_Result_CallAPI_IsActive();
  virtual void SetUp();
  virtual void TearDown();
  bool isSuccess(const std::string& msg);
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
