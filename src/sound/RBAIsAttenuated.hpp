/**
 * Attenuatedチェッククラス
 */

#ifndef RBAISATTENUATED_HPP
#define RBAISATTENUATED_HPP

#include "RBAZoneOperator.hpp"

namespace rba
{

class RBAExpression;

class DLL_EXPORT RBAIsAttenuated : public RBAZoneOperator
{
public:
  RBAIsAttenuated()=default;
  RBAIsAttenuated(const RBAIsAttenuated&)=delete;
  RBAIsAttenuated(const RBAIsAttenuated&&)=delete;
  RBAIsAttenuated& operator=(const RBAIsAttenuated&)=delete;
  RBAIsAttenuated& operator=(const RBAIsAttenuated&&)=delete;
  virtual ~RBAIsAttenuated()=default;

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
