/**
 * 変数クラスヘッダファイル
 */

#ifndef RBAVARIABLE_HPP
#define RBAVARIABLE_HPP

#include <memory>
#include "RBARuleObject.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

class DLL_EXPORT RBAVariable : public RBARuleObject
{
public:
  explicit RBAVariable(const std::string& name="");
  RBAVariable(const RBAVariable&)=delete;
  RBAVariable(const RBAVariable&&)=delete;
  RBAVariable& operator=(const RBAVariable&)=delete;
  RBAVariable& operator=(const RBAVariable&&)=delete;
  virtual ~RBAVariable()=default;

public:
  RBAModelElementType getModelElementType() const override;

  const RBARuleObject* getRuleObj() const;
  void setRuleObj(const RBARuleObject* const ruleObj);
  void clearRuleObj();
  RBAConstraintInfo* createConstraintInfo();
  std::shared_ptr<RBAConstraintInfo> getConstraintInfo() const;

private:
  const RBARuleObject* ruleObj_ {nullptr};
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::shared_ptr<RBAConstraintInfo> constraintInfo_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
