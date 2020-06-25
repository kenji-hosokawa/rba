/// 小なりイコールチェッククラスヘッダファイル

#ifndef RBAISLOWERTHANEQUALOPERATOR_HPP
#define RBAISLOWERTHANEQUALOPERATOR_HPP

#include "RBALogicalOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAIsLowerThanEqualOperator : public RBALogicalOperator
{
public:
  RBAIsLowerThanEqualOperator()=default;
  RBAIsLowerThanEqualOperator(const RBAIsLowerThanEqualOperator&)=delete;
  RBAIsLowerThanEqualOperator(RBAIsLowerThanEqualOperator&&)=delete;
  RBAIsLowerThanEqualOperator& operator=(const RBAIsLowerThanEqualOperator&)=delete;
  RBAIsLowerThanEqualOperator& operator=(RBAIsLowerThanEqualOperator&&)=delete;
  virtual ~RBAIsLowerThanEqualOperator()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
