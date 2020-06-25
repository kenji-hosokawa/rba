/**
 * アクティブチェッククラスヘッダファイル
 */

#ifndef RBAISACTIVE_HPP
#define RBAISACTIVE_HPP

#include "RBAContentOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAIsActive : public RBAContentOperator
{
public:
  RBAIsActive()=default;
  RBAIsActive(const RBAIsActive&)=delete;
  RBAIsActive(const RBAIsActive&&)=delete;
  RBAIsActive& operator=(const RBAIsActive&)=delete;
  RBAIsActive& operator=(const RBAIsActive&&)=delete;
  virtual ~RBAIsActive()=default;

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
