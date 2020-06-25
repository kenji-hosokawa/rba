//
// Selectオペレータ
//

#ifndef RBASELECTOPERATOR_HPP
#define RBASELECTOPERATOR_HPP

#include "RBALambdaContext.hpp"

namespace rba
{

class RBAAllocatableSet;
class RBAContentSet;

class RBASelectOperator : public RBALambdaContext
{
 public:
  RBASelectOperator();
  RBASelectOperator(const RBASelectOperator&)=delete;
  RBASelectOperator(const RBASelectOperator&&)=delete;
  RBASelectOperator& operator=(const RBASelectOperator&)=delete;
  RBASelectOperator& operator=(const RBASelectOperator&&)=delete;
  virtual ~RBASelectOperator()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitrator* arb) const override;

#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif
 private:
  std::unique_ptr<RBAAllocatableSet> allocatableSet_;
  std::unique_ptr<RBAContentSet> contentSet_;
};

} /* namespace rba */

#endif /* RBASELECTOPERATOR_HPP */
