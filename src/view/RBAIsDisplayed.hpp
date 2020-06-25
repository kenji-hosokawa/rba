/**
 *  Displayedチェッククラスヘッダファイル
 */

#ifndef RBAISDISPLAYED_HPP
#define RBAISDISPLAYED_HPP

#include "RBAAreaOperator.hpp"

namespace rba
{

class RBAExpression;

class DLL_EXPORT RBAIsDisplayed : public RBAAreaOperator
{
public:
  RBAIsDisplayed()=default;
  RBAIsDisplayed(const RBAIsDisplayed&)=delete;
  RBAIsDisplayed(const RBAIsDisplayed&&)=delete;
  RBAIsDisplayed& operator=(const RBAIsDisplayed&)=delete;
  RBAIsDisplayed& operator=(const RBAIsDisplayed&&)=delete;
  virtual ~RBAIsDisplayed()=default;

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
