/// 変数クラス定義ファイル

#include "RBAVariable.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAVariable::RBAVariable(const std::string& name)
  : RBARuleObject{name}
{
}

RBAModelElementType
RBAVariable::getModelElementType() const
{
  return RBAModelElementType::Variable;
}

const RBARuleObject*
RBAVariable::getRuleObj() const
{
  return ruleObj_;
}

void
RBAVariable::setRuleObj(const RBARuleObject* const ruleObj)
{
  ruleObj_ = ruleObj;
}

void
RBAVariable::clearRuleObj()
{
  ruleObj_ = nullptr;
}

RBAConstraintInfo*
RBAVariable::createConstraintInfo()
{
  // Let式がFor-Allなどのラムダ式の中に書かれた場合、
  // For-Allのxなどのvaliableが変化するたびに、Let式の展開結果も変化する。
  // Let式がFor-Allの中に掛かれていたとしても、
  // しかし、そのvaliableオブジェクトは1つしかないよって、
  // constraintInfoをクリアして使い回すことは出来ず、
  // Let式を評価するたびに、make_sharedする必要がある。
  // なお、Let式のConstraintInfoは、Let式の定義を参照しているRBAObjectReference評価時に
  // そのRBAObjectReferenceのConstraintInfoの下に所有権が移る。
  constraintInfo_ = std::make_shared<RBAConstraintInfo>();
  return constraintInfo_.get();
}

std::shared_ptr<RBAConstraintInfo>
RBAVariable::getConstraintInfo() const
{
  return constraintInfo_;
}

}
