//
// Maxオペレータヘッダーファイル
//

#ifndef RBAMAXOPERATOR_HPP
#define RBAMAXOPERATOR_HPP

#include "RBALambdaContext.hpp"

namespace rba
{

class RBAMaxOperator : public RBALambdaContext
{
 public:
  RBAMaxOperator()=default;
  RBAMaxOperator(const RBAMaxOperator&)=delete;
  RBAMaxOperator(const RBAMaxOperator&&)=delete;
  RBAMaxOperator& operator=(const RBAMaxOperator&)=delete;
  RBAMaxOperator& operator=(const RBAMaxOperator&&)=delete;
  virtual ~RBAMaxOperator()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitrator* arb) const override;

#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif
};

} /* namespace rba */

#endif /* RBAMAXOPERATOR_HPP */
