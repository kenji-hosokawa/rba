/**
 * Outputtedチェッククラス
 */

#ifndef RBAISOUTPUTTED_HPP
#define RBAISOUTPUTTED_HPP

#include <string>
#include "RBAZoneOperator.hpp"

namespace rba
{

class RBAExpression;

class DLL_EXPORT RBAIsOutputted : public RBAZoneOperator
{
public:
  RBAIsOutputted()=default;
  RBAIsOutputted(const RBAIsOutputted&)=delete;
  RBAIsOutputted(const RBAIsOutputted&&)=delete;
  RBAIsOutputted& operator=(const RBAIsOutputted&)=delete;
  RBAIsOutputted& operator=(const RBAIsOutputted&&)=delete;
  virtual ~RBAIsOutputted()=default;

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
