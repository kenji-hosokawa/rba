/**
 * 制約実装クラスヘッダファイル
 */

#ifndef RBACONSTRAINTIMPL_HPP
#define RBACONSTRAINTIMPL_HPP

#include "RBAConstraint.hpp"
#include "RBAAbstractConstraint.hpp"

namespace rba
{

class RBAArbitrator;

class DLL_EXPORT RBAConstraintImpl : public RBAConstraint,
				                             public RBAAbstractConstraint
{
public:
  explicit RBAConstraintImpl(const std::string& name="");
  RBAConstraintImpl(const RBAConstraintImpl&)=delete;
  RBAConstraintImpl(const RBAConstraintImpl&&)=delete;
  RBAConstraintImpl& operator=(const RBAConstraintImpl&)=delete;
  RBAConstraintImpl& operator=(const RBAConstraintImpl&&)=delete;
  virtual ~RBAConstraintImpl()=default;

public:
  void setRuntime(const bool newRuntime);
  std::string getName() const override;
  bool isConstraint() const override;
  bool isRuntime() const;
  bool execute(RBAArbitrator* const arb);

private:
  bool runtime_ {RUNTIME_EDEFAULT};
};

}

#endif
