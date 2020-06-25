/**
 * オブジェクト比較クラスヘッダファイル
 */

#ifndef RBAOBJECTCOMPARE_HPP
#define RBAOBJECTCOMPARE_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAObjectCompare : public RBAOperator
{
public:
  RBAObjectCompare()=default;
  RBAObjectCompare(const RBAObjectCompare&)=delete;
  RBAObjectCompare(const RBAObjectCompare&&)=delete;
  RBAObjectCompare& operator=(const RBAObjectCompare&)=delete;
  RBAObjectCompare& operator=(const RBAObjectCompare&&)=delete;
  virtual ~RBAObjectCompare()=default;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
