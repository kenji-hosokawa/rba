// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI_mute.hpp
 */

#ifndef RESULTAPI_MUTE_HPP
#define RESULTAPI_MUTE_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"
#include "ResultAPI.hpp"

namespace resultapi {

using namespace rba;

/*
 * muteテスト
 */
class ResultAPI_mute : public ResultAPI
{
protected:
  ResultAPI_mute();
  virtual ~ResultAPI_mute();
};

}
#endif
