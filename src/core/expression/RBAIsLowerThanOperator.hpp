/// 小なりチェックオペレータクラスヘッダファイル

#ifndef RBAISLOWERTHANOPERATOR_HPP
#define RBAISLOWERTHANOPERATOR_HPP

#include "RBALogicalOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAIsLowerThanOperator : public RBALogicalOperator
{
public:
  RBAIsLowerThanOperator()=default;
  RBAIsLowerThanOperator(const RBAIsLowerThanOperator&)=delete;
  RBAIsLowerThanOperator(RBAIsLowerThanOperator&&)=delete;
  RBAIsLowerThanOperator& operator=(const RBAIsLowerThanOperator&)=delete;
  RBAIsLowerThanOperator& operator=(RBAIsLowerThanOperator&&)=delete;
  virtual ~RBAIsLowerThanOperator()=default;

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
