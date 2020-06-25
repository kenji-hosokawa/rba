/**
 * ビジブルチェッククラスヘッダファイル
 */

#ifndef RBAISVISIBLE_HPP
#define RBAISVISIBLE_HPP

#include <string>
#include "RBAViewContentOperator.hpp"

namespace rba
{

class RBAViewContentImpl;

class DLL_EXPORT RBAIsVisible : public RBAViewContentOperator
{
public:
  RBAIsVisible()=default;
  RBAIsVisible(const RBAIsVisible&)=delete;
  RBAIsVisible(const RBAIsVisible&&)=delete;
  RBAIsVisible& operator=(const RBAIsVisible&)=delete;
  RBAIsVisible& operator=(const RBAIsVisible&&)=delete;
  virtual ~RBAIsVisible()=default;

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
