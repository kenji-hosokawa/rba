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
 * AllInstanceOfViewContent class header file
 */

#ifndef RBAALLINSRTANCEOFVIEWCONTENTIMPL_HPP
#define RBAALLINSRTANCEOFVIEWCONTENTIMPL_HPP

#include "RBASetExpression.hpp"
#include "RBAViewContentSet.hpp"

namespace rba
{

class DLL_EXPORT RBAAllInstanceOfViewContent : public RBASetExpression
{
public:
  RBAAllInstanceOfViewContent()=default;
  RBAAllInstanceOfViewContent(const RBAAllInstanceOfViewContent&)=delete;
  RBAAllInstanceOfViewContent(const RBAAllInstanceOfViewContent&&)=delete;
  RBAAllInstanceOfViewContent& operator=(const RBAAllInstanceOfViewContent&)=delete;
  RBAAllInstanceOfViewContent& operator=(const RBAAllInstanceOfViewContent&&)=delete;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitrator* arb) const override;
  void setContents(const std::list<const RBAViewContentImpl*>& contents);

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

private:
  RBAViewContentSet allViewContentSet_;

};

}

#endif
