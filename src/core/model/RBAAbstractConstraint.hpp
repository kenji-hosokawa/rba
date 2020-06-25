/**
 * 制約式の抽象クラスのヘッダファイル
 */

#ifndef RBAABSTRACTCONSTRAINT_HPP
#define RBAABSTRACTCONSTRAINT_HPP

#include <memory>
#include "RBANamedElement.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

class RBAExpression;

class DLL_EXPORT RBAAbstractConstraint : public RBANamedElement
{
protected:
  explicit RBAAbstractConstraint(const std::string& name);
  RBAAbstractConstraint(const RBAAbstractConstraint&)=delete;
  RBAAbstractConstraint(const RBAAbstractConstraint&&)=delete;
  RBAAbstractConstraint& operator=(const RBAAbstractConstraint&)=delete;
  RBAAbstractConstraint& operator=(const RBAAbstractConstraint&&)=delete;
  void clearInfo();

public:
  virtual ~RBAAbstractConstraint()=default;
  virtual bool isConstraint() const;
  virtual bool isRule() const;
  virtual void setExpression(RBAExpression*);
  virtual RBAExpression* const getExpression() const;
  RBAConstraintInfo* getInfo() const;

  // Log
#ifdef RBA_USE_LOG
  virtual void createHierarchy();
#endif

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unique_ptr<RBAConstraintInfo> info_ {std::make_unique<RBAConstraintInfo>()};
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  RBAExpression* expression_ {nullptr};

};

}

#endif
