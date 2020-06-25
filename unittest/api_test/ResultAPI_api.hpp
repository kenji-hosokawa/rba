// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_api.hpp
 */

#ifndef RESULTAPI_API_HPP
#define RESULTAPI_API_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"
#include "ResultAPI.hpp"

namespace resultapi {

using namespace rba;

/**
 * APIテスト
 */
class ResultAPI_api : public ResultAPI
{
protected:
  ResultAPI_api();
  virtual ~ResultAPI_api();
};

}
#endif
