/// @file  RBAActiveStateMaker.hpp
/// @brief ActiveState object maker class header ///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAACTIVESTATEMAKER_HPP
#define RBAACTIVESTATEMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief ActiveState object maker class
class RBAActiveStateMaker : public RBAOperatorMaker
{
public:
  RBAActiveStateMaker();
  RBAActiveStateMaker(const RBAActiveStateMaker&)=delete;
  RBAActiveStateMaker(const RBAActiveStateMaker&&)=delete;
  RBAActiveStateMaker& operator=(const RBAActiveStateMaker&)=delete;
  RBAActiveStateMaker& operator=(const RBAActiveStateMaker&&)=delete;
  virtual ~RBAActiveStateMaker()=default;

protected:
  /// @brief Empty instanciation
  /// @details Create an empty instance of unique_ptr in a derived class
  /// @return unique_ptr of instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif
