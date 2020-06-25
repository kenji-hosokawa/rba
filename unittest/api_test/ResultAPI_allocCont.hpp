// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_result_api.hpp
 */

#ifndef RESULTAPI_ALLOCCONT_HPP
#define RESULTAPI_ALLOCCONT_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"
#include "ResultAPI.hpp"

namespace resultapi {

using namespace rba;

/*
 * Allocatable-Contentテスト
 */
class ResultAPI_allocCont : public ResultAPI
{
protected:
  ResultAPI_allocCont();
  virtual ~ResultAPI_allocCont();
};

}
#endif
