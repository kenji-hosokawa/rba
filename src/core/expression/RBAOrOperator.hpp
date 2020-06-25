/**
 * ORオペレータクラスヘッダファイル
 */

#ifndef RBAOROPERATOR_HPP
#define RBAOROPERATOR_HPP

#include "RBALogicalOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAOrOperator : public RBALogicalOperator
{
 public:
  RBAOrOperator()=default;
  RBAOrOperator(const RBAOrOperator&)=delete;
  RBAOrOperator(const RBAOrOperator&&)=delete;
  RBAOrOperator& operator=(const RBAOrOperator&)=delete;
  RBAOrOperator& operator=(const RBAOrOperator&&)=delete;
  virtual ~RBAOrOperator()=default;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
#endif

};

}

#endif
