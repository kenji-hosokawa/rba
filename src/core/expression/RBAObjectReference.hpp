/**
 * オブジェクトリファレンスクラスヘッダファイル
 */

#ifndef RBAOBJECTREFERENCE_HPP
#define RBAOBJECTREFERENCE_HPP

#include "RBAExpression.hpp"

namespace rba
{

class DLL_EXPORT RBAObjectReference : public RBAExpression
{
public:
  RBAObjectReference()=default;
  RBAObjectReference(const RBAObjectReference&)=delete;
  RBAObjectReference(const RBAObjectReference&&)=delete;
  RBAObjectReference& operator=(const RBAObjectReference&)=delete;
  RBAObjectReference& operator=(const RBAObjectReference&&)=delete;
  virtual ~RBAObjectReference()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitrator* arb) const override;
  void setRefObject(const RBARuleObject* const newRefObject);

  // Log
#ifdef RBA_USE_LOG
  void setExpressionType(RBAExpressionType const newExprType);
  void createHierarchy() override;
  const std::string getExpressionText() const override;
  RBAExpressionType getUnderlyingType() const override;
  const std::string getCoverageExpressionText() const override;
#endif

private:
  const RBARuleObject* refObject_;
#ifdef RBA_USE_LOG
  RBAExpressionType expressionType_;
#endif

};

}

#endif
