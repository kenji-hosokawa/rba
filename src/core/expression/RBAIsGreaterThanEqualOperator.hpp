/// 大なりイコールチェックオペレータクラスヘッダファイル

#ifndef RBAISGREATERTHANEQUALOPERATOR_HPP
#define RBAISGREATERTHANEQUALOPERATOR_HPP

#include "RBALogicalOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAIsGreaterThanEqualOperator : public RBALogicalOperator
{
public:
  RBAIsGreaterThanEqualOperator()=default;
  RBAIsGreaterThanEqualOperator(const RBAIsGreaterThanEqualOperator&)=delete;
  RBAIsGreaterThanEqualOperator(RBAIsGreaterThanEqualOperator&&)=delete;
  RBAIsGreaterThanEqualOperator& operator=(const RBAIsGreaterThanEqualOperator&)=delete;
  RBAIsGreaterThanEqualOperator& operator=(RBAIsGreaterThanEqualOperator&&)=delete;
  virtual ~RBAIsGreaterThanEqualOperator()=default;

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
