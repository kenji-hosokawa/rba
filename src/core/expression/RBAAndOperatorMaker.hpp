/// @file  RBAAndOperatorMaker.hpp
/// @brief AndOperator object maker classs header file
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAANDOPERATORMAKER_HPP
#define RBAANDOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief AndOperator object maker classs
class RBAAndOperatorMaker : public RBAOperatorMaker
{
public:
  RBAAndOperatorMaker();
  RBAAndOperatorMaker(const RBAAndOperatorMaker&)=delete;
  RBAAndOperatorMaker(const RBAAndOperatorMaker&&)=delete;
  RBAAndOperatorMaker& operator=(const RBAAndOperatorMaker&)=delete;
  RBAAndOperatorMaker& operator=(const RBAAndOperatorMaker&&)=delete;
  virtual ~RBAAndOperatorMaker()=default;

protected:
  /// @brief Empty instanciation
  /// @details Create an empty instance of unique_ptr in a derived class
  /// @return unique_ptr of instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif
