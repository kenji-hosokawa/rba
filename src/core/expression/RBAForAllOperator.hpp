/**
 * ForAllオペレータクラスヘッダファイル
 */

#ifndef RBAFORALLOPERATOR_HPP
#define RBAFORALLOPERATOR_HPP

#include "RBALambdaContext.hpp"

namespace rba
{

class DLL_EXPORT RBAForAllOperator : public RBALambdaContext
{
public:
  RBAForAllOperator()=default;
  RBAForAllOperator(const RBAForAllOperator&)=delete;
  RBAForAllOperator(const RBAForAllOperator&&)=delete;
  RBAForAllOperator& operator=(const RBAForAllOperator&)=delete;
  RBAForAllOperator& operator=(const RBAForAllOperator&&)=delete;
  virtual ~RBAForAllOperator()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
