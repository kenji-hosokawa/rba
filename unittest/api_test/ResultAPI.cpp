// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * ResultAPI.cpp
 */

#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "ResultAPI.hpp"

namespace resultapi {

using namespace rba;

ResultAPI::ResultAPI()
{
}

ResultAPI::~ResultAPI()
{
}

void ResultAPI::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(jsonFile));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void ResultAPI::TearDown()
{
  if(arb_) {
    delete arb_;
    arb_ = nullptr;
  }
  if(model_) {
    delete model_;
    model_ = nullptr;
  }
}

bool ResultAPI::hasObject(const std::list<const RBAArea*>& areas,
			  const std::string& name)
{
  for(const RBAArea* area : areas) {
    if(area->getName() == name) {
      return true;
    }
  }

  return false;
}

bool ResultAPI::hasObject(const std::list<const RBAZone*>& zones,
			  const std::string& name)
{
  for(const RBAZone* zone : zones) {
    if(zone->getName() == name) {
      return true;
    }
  }

  return false;
}

bool ResultAPI::hasObject(const std::list<const RBAScene*>& scenes,
			  const std::string& name)
{
  for(const RBAScene* scene : scenes) {
    if(scene->getName() == name) {
      return true;
    }
  }

  return false;
}

bool ResultAPI::hasObject(const std::list<const RBAViewContentState*>& states,
			  const std::string& uniqueName)
{
  for(const RBAViewContentState* state : states) {
    if(state->getUniqueName() == uniqueName) {
      return true;
    }
  }

  return false;
}

bool ResultAPI::hasObject(const std::list<const RBASoundContentState*>& states,
			  const std::string& uniqueName)
{
  for(const RBASoundContentState* state : states) {
    if(state->getUniqueName() == uniqueName) {
      return true;
    }
  }

  return false;
}

bool ResultAPI::hasObject(const std::list<const RBAViewContent*>& contents,
			  const std::string& name)
{
  for(const RBAViewContent* content : contents) {
    if(content->getName() == name) {
      return true;
    }
  }

  return false;
}

bool ResultAPI::hasObject(const std::list<const RBASoundContent*>& contents,
			  const std::string& name)
{
  for(const RBASoundContent* content : contents) {
    if(content->getName() == name) {
      return true;
    }
  }

  return false;
}

}
