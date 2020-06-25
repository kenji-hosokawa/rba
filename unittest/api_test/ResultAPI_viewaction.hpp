// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_viewaction.hpp
 */

#ifndef RESULTAPI_VIEWACTION_HPP
#define RESULTAPI_VIEWACTION_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"
#include "ResultAPI.hpp"

namespace resultapi {

using namespace rba;

/**
 * APIテスト
 */
class ResultAPI_viewaction : public ResultAPI
{
protected:
  ResultAPI_viewaction();
  virtual ~ResultAPI_viewaction();
};

}
#endif
