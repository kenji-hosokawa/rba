/**
 * NOTオペレータクラスヘッダファイル
 */

#ifndef RBANOTOPERATOR_HPP
#define RBANOTOPERATOR_HPP

#include "RBALogicalOperator.hpp"

namespace rba
{

class DLL_EXPORT RBANotOperator : public RBALogicalOperator
{
public:
  RBANotOperator()=default;
  RBANotOperator(const RBANotOperator&)=delete;
  RBANotOperator(const RBANotOperator&&)=delete;
  RBANotOperator& operator=(const RBANotOperator&)=delete;
  RBANotOperator& operator=(const RBANotOperator&&)=delete;
  virtual ~RBANotOperator()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

};

}

#endif
