/// イコールチェックオペレータクラス定義ファイル

#ifndef RBAISEQUALTOOPERATOR_HPP
#define RBAISEQUALTOOPERATOR_HPP

#include "RBALogicalOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAIsEqualToOperator : public RBALogicalOperator
{
public:
  RBAIsEqualToOperator()=default;
  RBAIsEqualToOperator(const RBAIsEqualToOperator&)=delete;
  RBAIsEqualToOperator(RBAIsEqualToOperator&&)=delete;
  RBAIsEqualToOperator& operator=(const RBAIsEqualToOperator&)=delete;
  RBAIsEqualToOperator& operator=(RBAIsEqualToOperator&&)=delete;
  virtual ~RBAIsEqualToOperator()=default;

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
