/**
 * Allocatable operator class header
 */

#ifndef RBAALLOCATABLEOPERATOR_HPP
#define RBAALLOCATABLEOPERATOR_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAAllocatableOperator : public RBAOperator
{
protected:
  RBAAllocatableOperator()=default;
  RBAAllocatableOperator(const RBAAllocatableOperator&)=delete;
  RBAAllocatableOperator(const RBAAllocatableOperator&&)=delete;
  RBAAllocatableOperator& operator=(const RBAAllocatableOperator&)=delete;
  RBAAllocatableOperator& operator=(const RBAAllocatableOperator&&)=delete;

public:
  virtual ~RBAAllocatableOperator()=default;
  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

};

}

#endif
