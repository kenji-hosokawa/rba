/// 
/// ContentValue class header file 
///

#ifndef RBACONTENTVALUE_HPP
#define RBACONTENTVALUE_HPP

#include <cstdint>
#include "RBAAllocatableOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAContentValue : public RBAAllocatableOperator
{
public:
  RBAContentValue()=default;
  RBAContentValue(const RBAContentValue&)=delete;
  RBAContentValue(RBAContentValue&&)=delete;
  RBAContentValue& operator=(const RBAContentValue&)=delete;
  RBAContentValue& operator=(RBAContentValue&&)=delete;
  virtual ~RBAContentValue()=default;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                            RBAArbitrator* arb) const override;

#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
#endif

};

}

#endif
