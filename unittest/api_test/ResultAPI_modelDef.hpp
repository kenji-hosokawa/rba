// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_modelDef.hpp
 */

#ifndef RESULTAPI_MODELDEF_HPP
#define RESULTAPI_MODELDEF_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"
#include "ResultAPI.hpp"

namespace resultapi {

using namespace rba;

/*
 * モデル定義順テスト
 */
class ResultAPI_modelDef : public ResultAPI
{
protected:
  ResultAPI_modelDef();
  virtual ~ResultAPI_modelDef();
};

}
#endif
