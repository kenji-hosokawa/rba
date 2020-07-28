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
/// @file  RBAIsDisplayedMaker.hpp
/// @brief IsDisplayed object generation class header

#ifndef RBAISDISPLAYEDMAKER_HPP
#define RBAISDISPLAYEDMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief IsDisplayed object generation class
class RBAIsDisplayedMaker : public RBAOperatorMaker
{
public:
  RBAIsDisplayedMaker();
  RBAIsDisplayedMaker(const RBAIsDisplayedMaker&)=delete;
  RBAIsDisplayedMaker(const RBAIsDisplayedMaker&&)=delete;
  RBAIsDisplayedMaker& operator=(const RBAIsDisplayedMaker&)=delete;
  RBAIsDisplayedMaker& operator=(const RBAIsDisplayedMaker&&)=delete;
  virtual ~RBAIsDisplayedMaker()=default;

protected:
  /// @brief create empty instance
  /// @details Create an empty instance of unique_ptr in your derived class.
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif
