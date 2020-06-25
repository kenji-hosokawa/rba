/**
 * シーンのアクティブ判定クラスヘッダファイル
 */

#ifndef RBAISON_HPP
#define RBAISON_HPP

#include "RBASceneOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAIsOn : public RBASceneOperator
{
public:
  RBAIsOn()=default;
  RBAIsOn(const RBAIsOn&)=delete;
  RBAIsOn(const RBAIsOn&&)=delete;
  RBAIsOn& operator=(const RBAIsOn&)=delete;
  RBAIsOn& operator=(const RBAIsOn&&)=delete;
  virtual ~RBAIsOn()=default;

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
