/// 大なりチェックオペレータクラスヘッダファイル

#ifndef RBAISGREATERTHANOPERATOR_HPP
#define RBAISGREATERTHANOPERATOR_HPP

#include "RBALogicalOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAIsGreaterThanOperator : public RBALogicalOperator
{
public:
  RBAIsGreaterThanOperator()=default;
  RBAIsGreaterThanOperator(const RBAIsGreaterThanOperator&)=delete;
  RBAIsGreaterThanOperator(RBAIsGreaterThanOperator&&)=delete;
  RBAIsGreaterThanOperator& operator=(const RBAIsGreaterThanOperator&)=delete;
  RBAIsGreaterThanOperator& operator=(RBAIsGreaterThanOperator&&)=delete;
  virtual ~RBAIsGreaterThanOperator()=default;

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
