/**
 * 後行要求判定クラスヘッダファイル
 */

#ifndef RBAHASCOMELATERTHAN_HPP
#define RBAHASCOMELATERTHAN_HPP

#include "RBAContentOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAHasComeLaterThan : public RBAContentOperator
{
public:
  RBAHasComeLaterThan()=default;
  RBAHasComeLaterThan(const RBAHasComeLaterThan&)=delete;
  RBAHasComeLaterThan(const RBAHasComeLaterThan&&)=delete;
  RBAHasComeLaterThan& operator=(const RBAHasComeLaterThan&)=delete;
  RBAHasComeLaterThan& operator=(const RBAHasComeLaterThan&&)=delete;
  virtual ~RBAHasComeLaterThan()=default;

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
