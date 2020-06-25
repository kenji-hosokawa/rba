/**
 * Hiddenチェッククラスヘッダファイル
 */

#ifndef RBAISHIDDEN_HPP
#define RBAISHIDDEN_HPP

#include <string>
#include "RBAAreaOperator.hpp"

namespace rba
{

class RBAExpression;

class DLL_EXPORT RBAIsHidden : public RBAAreaOperator
{
public:
  RBAIsHidden()=default;
  RBAIsHidden(const RBAIsHidden&)=delete;
  RBAIsHidden(const RBAIsHidden&&)=delete;
  RBAIsHidden& operator=(const RBAIsHidden&)=delete;
  RBAIsHidden& operator=(const RBAIsHidden&&)=delete;
  virtual ~RBAIsHidden()=default;

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
