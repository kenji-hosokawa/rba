/**
 * Allocated Content class
 */

#ifndef RBAALLOCATEDCONTENT_HPP
#define RBAALLOCATEDCONTENT_HPP

#include "RBAAllocatableOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAAllocatedContent : public RBAAllocatableOperator
{
 public:
  RBAAllocatedContent()=default;
  RBAAllocatedContent(const RBAAllocatedContent&)=delete;
  RBAAllocatedContent(const RBAAllocatedContent&&)=delete;
  RBAAllocatedContent& operator=(const RBAAllocatedContent&)=delete;
  RBAAllocatedContent& operator=(const RBAAllocatedContent&&)=delete;
  virtual ~RBAAllocatedContent()=default;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitrator* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  void createHierarchy() override;
#endif

};

}

#endif
