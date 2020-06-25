// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_hidden.hpp
 */

#ifndef RESULTAPI_HIDDEN_HPP
#define RESULTAPI_HIDDEN_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"
#include "ResultAPI.hpp"

namespace resultapi {

using namespace rba;

/*
 * hiddenテスト
 */
class ResultAPI_hidden : public ResultAPI
{
protected:
  ResultAPI_hidden();
  virtual ~ResultAPI_hidden();
};

}
#endif
