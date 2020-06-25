/// Minオペレータヘッダーファイル

#ifndef RBAMINOPERATOR_HPP
#define RBAMINOPERATOR_HPP

#include "RBALambdaContext.hpp"

namespace rba
{

class RBAMinOperator : public RBALambdaContext
{
 public:
  RBAMinOperator()=default;
  RBAMinOperator(const RBAMinOperator&)=delete;
  RBAMinOperator(RBAMinOperator&&)=delete;
  RBAMinOperator& operator=(const RBAMinOperator&)=delete;
  RBAMinOperator& operator=(RBAMinOperator&&)=delete;
  virtual ~RBAMinOperator()=default;

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

} // namespace rba

#endif // RBAMINOPERATOR_HPP
