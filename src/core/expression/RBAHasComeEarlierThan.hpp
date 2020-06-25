/**
 * 先行要求判定クラスヘッダファイル
 */

#ifndef RBAHASCOMEEARLIERTHAN_HPP
#define RBAHASCOMEEARLIERTHAN_HPP

#include "RBAContentOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAHasComeEarlierThan : public RBAContentOperator
{
public:
  RBAHasComeEarlierThan()=default;
  RBAHasComeEarlierThan(const RBAHasComeEarlierThan&)=delete;
  RBAHasComeEarlierThan(const RBAHasComeEarlierThan&&)=delete;
  RBAHasComeEarlierThan& operator=(const RBAHasComeEarlierThan&)=delete;
  RBAHasComeEarlierThan& operator=(const RBAHasComeEarlierThan&&)=delete;
  virtual ~RBAHasComeEarlierThan()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator* arb) const override;

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
