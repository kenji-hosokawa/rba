/**
 * Exists operator Class header file
 */

#ifndef RBAEXISTSOPERATOR_HPP
#define RBAEXISTSOPERATOR_HPP

#include "RBALambdaContext.hpp"

namespace rba
{

class DLL_EXPORT RBAExistsOperator : public RBALambdaContext
{
public:
  RBAExistsOperator()=default;
  RBAExistsOperator(const RBAExistsOperator&)=delete;
  RBAExistsOperator(const RBAExistsOperator&&)=delete;
  RBAExistsOperator& operator=(const RBAExistsOperator&)=delete;
  RBAExistsOperator& operator=(const RBAExistsOperator&&)=delete;
  virtual ~RBAExistsOperator()=default;

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
