/**
 * Copyright (c) 2019 DENSO CORPORATION.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * HasComeLaterThan class
 */

#ifndef RBAHASCOMELATERTHAN_HPP
#define RBAHASCOMELATERTHAN_HPP

#include "RBAContentOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAHasComeLaterThan : public RBAContentOperator
{
public:
  RBAHasComeLaterThan()=default;
  RBAHasComeLaterThan(const RBAHasComeLaterThan&)=delete;
  RBAHasComeLaterThan(const RBAHasComeLaterThan&&)=delete;
  RBAHasComeLaterThan& operator=(const RBAHasComeLaterThan&)=delete;
  RBAHasComeLaterThan& operator=(const RBAHasComeLaterThan&&)=delete;
  virtual ~RBAHasComeLaterThan()=default;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
