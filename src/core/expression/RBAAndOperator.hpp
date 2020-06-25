/**
 * ANDオペレータクラスヘッダファイル
 */

#ifndef RBAANDOPERATOR_HPP
#define RBAANDOPERATOR_HPP

#include "RBALogicalOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAAndOperator : public RBALogicalOperator
{
 public:
  RBAAndOperator()=default;
  RBAAndOperator(const RBAAndOperator&)=delete;
  RBAAndOperator(const RBAAndOperator&&)=delete;
  RBAAndOperator& operator=(const RBAAndOperator&)=delete;
  RBAAndOperator& operator=(const RBAAndOperator&&)=delete;
  virtual ~RBAAndOperator()=default;

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
