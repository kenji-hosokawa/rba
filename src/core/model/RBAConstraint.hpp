// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * 制約式クラス
 */

#ifndef RBACONSTRAINT_HPP
#define RBACONSTRAINT_HPP

#include <string>
#include "RBADllExport.hpp"

namespace rba
{

class DLL_EXPORT RBAConstraint
{
 public:
  RBAConstraint()=default;
  RBAConstraint(const RBAConstraint&)=delete;
  RBAConstraint(const RBAConstraint&&)=delete;
  RBAConstraint& operator=(const RBAConstraint&)=delete;
  RBAConstraint& operator=(const RBAConstraint&&)=delete;
  virtual ~RBAConstraint() = default;
  virtual std::string getName() const =0;
  const static bool RUNTIME_EDEFAULT = true;
};

}

#endif
