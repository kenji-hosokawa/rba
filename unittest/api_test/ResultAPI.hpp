// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI.hpp
 */

#ifndef RESULTAPI_HPP
#define RESULTAPI_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE_API			"ResultAPI_api.json"
#define JSONFILE_ALLOCATABLE_CONTENT	"ResultAPI_allocCont.json"

namespace resultapi {

using namespace rba;

class ResultAPI : public ::testing::Test
{
protected:
  ResultAPI();
  virtual ~ResultAPI();
  virtual void SetUp();
  virtual void TearDown();
  bool hasObject(const std::list<const RBAArea*>& areas, const std::string& name);
  bool hasObject(const std::list<const RBAZone*>& zones, const std::string& name);
  bool hasObject(const std::list<const RBAScene*>& scenes, const std::string& name);
  bool hasObject(const std::list<const RBAViewContentState*>& states,
		 const std::string& uniqueName);
  bool hasObject(const std::list<const RBASoundContentState*>& states,
		 const std::string& uniqueName);
  bool hasObject(const std::list<const RBAViewContent*>& contents,
		 const std::string& name);
  bool hasObject(const std::list<const RBASoundContent*>& contents,
		 const std::string& name);

protected:
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  std::unique_ptr<RBAResult> result_=nullptr;
  std::string jsonFile="";
};

}
#endif
