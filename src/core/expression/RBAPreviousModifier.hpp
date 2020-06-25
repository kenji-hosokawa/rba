/**
 * 調停前参照クラスヘッダファイル
 */

#ifndef RBAPREVIOUSMODIFIER_HPP
#define RBAPREVIOUSMODIFIER_HPP

#include <memory>
#include "RBAExpression.hpp"

namespace rba
{

class RBAPreviousObjectWrapper;

class DLL_EXPORT RBAPreviousModifier : public RBAExpression
{
public:
  RBAPreviousModifier();
  RBAPreviousModifier(const RBAPreviousModifier&)=delete;
  RBAPreviousModifier(const RBAPreviousModifier&&)=delete;
  RBAPreviousModifier& operator=(const RBAPreviousModifier&)=delete;
  RBAPreviousModifier& operator=(const RBAPreviousModifier&&)=delete;
  virtual ~RBAPreviousModifier()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  void setObjReference(RBAExpression* const newObjRef);
  RBAExpression* const getObjReference() const;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitrator* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  virtual const std::string getSymbol() const;
  void createHierarchy() override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif

private:
  // objReference_->getReferenceObject()を呼び出すためconstにしない。
  RBAExpression* objReference_;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unique_ptr<RBAPreviousObjectWrapper> previousObj_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
