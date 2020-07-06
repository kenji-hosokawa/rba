/// @file  RBAActiveContentsMaker.hpp
/// @brief ActiveContents object creation class header
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAACTIVECONTENTSMAKER_HPP
#define RBAACTIVECONTENTSMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief ActiveContents object creation class
class RBAActiveContentsMaker : public RBAOperatorMaker
{
public:
  RBAActiveContentsMaker();
  RBAActiveContentsMaker(const RBAActiveContentsMaker&)=delete;
  RBAActiveContentsMaker(const RBAActiveContentsMaker&&)=delete;
  RBAActiveContentsMaker& operator=(const RBAActiveContentsMaker&)=delete;
  RBAActiveContentsMaker& operator=(const RBAActiveContentsMaker&&)=delete;
  virtual ~RBAActiveContentsMaker()=default;

public:
  /// @brief Empty instanciation
  /// @details Create an empty instance of unique_ptr in a derived class
  /// @return unique_ptr of instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif
