/**
 * 音声出力クラス
 */

#ifndef RBAOUTPUTTINGSOUND_HPP
#define RBAOUTPUTTINGSOUND_HPP

#include <string>
#include "RBAZoneOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAOutputtingSound : public RBAZoneOperator
{
public:
  RBAOutputtingSound()=default;
  RBAOutputtingSound(const RBAOutputtingSound&)=delete;
  RBAOutputtingSound(const RBAOutputtingSound&&)=delete;
  RBAOutputtingSound& operator=(const RBAOutputtingSound&)=delete;
  RBAOutputtingSound& operator=(const RBAOutputtingSound&&)=delete;
  virtual ~RBAOutputtingSound()=default;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitrator* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
