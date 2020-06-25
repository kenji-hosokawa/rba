// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * TestCommon.hpp
 */

#ifndef TESTCOMMON_HPP
#define TESTCOMMON_HPP

#include <string>
#include "RBAArea.hpp"
#include "RBAViewContent.hpp"
#include "RBAViewContentState.hpp"
#include "RBASize.hpp"
#include "RBAZone.hpp"
#include "RBASoundContent.hpp"
#include "RBASoundContentState.hpp"
#include "RBAScene.hpp"
#include "RBADisplay.hpp"
#include "RBAJsonParser.hpp"
#include "RBAModel.hpp"
#include "RBAArbitrationPolicy.hpp"
#include "RBAResultStatusType.hpp"
#include "RBAViewAction.hpp"
#include "RBAViewActionType.hpp"
#include "RBAArbitrator.hpp"

#ifndef JSONPATH
#ifdef RBA_USE_LCOV
#define JSONPATH    "../rba/unittest/logic_test"
#else
#define JSONPATH    "logic_test"
#endif
#endif

#define GET_JSON_PATH(json)   (std::string(JSONPATH)+"/"+std::string(json))

#endif
