/**
 * Mutedチェッククラスヘッダファイル
 */

#ifndef RBAISMUTED_HPP
#define RBAISMUTED_HPP

#include <string>
#include "RBAZoneOperator.hpp"

namespace rba
{

class RBAExpression;

class DLL_EXPORT RBAIsMuted : public RBAZoneOperator
{
public:
  RBAIsMuted()=default;
  RBAIsMuted(const RBAIsMuted&)=delete;
  RBAIsMuted(const RBAIsMuted&&)=delete;
  RBAIsMuted& operator=(const RBAIsMuted&)=delete;
  RBAIsMuted& operator=(const RBAIsMuted&&)=delete;
  virtual ~RBAIsMuted()=default;

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
