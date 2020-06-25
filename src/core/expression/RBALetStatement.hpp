/**
 * Let式クラスヘッダファイル
 */

#ifndef RBALETOPERATOR_HPP_
#define RBALETOPERATOR_HPP_

#include "RBAOperator.hpp"

namespace rba {

class RBAVariable;

class DLL_EXPORT RBALetStatement : public RBAOperator
{
public:
  RBALetStatement()=default;
  RBALetStatement(const RBALetStatement&)=delete;
  RBALetStatement(const RBALetStatement&&)=delete;
  RBALetStatement& operator=(const RBALetStatement&)=delete;
  RBALetStatement& operator=(const RBALetStatement&&)=delete;
  virtual ~RBALetStatement()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  void setVariable(RBAVariable* const var);
  void setVariable(RBAArbitrator* const arb);

private:
  RBAVariable* variable_;

};

}

#endif
