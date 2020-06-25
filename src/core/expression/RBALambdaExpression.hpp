/**
 * ラムダ式クラスヘッダファイル
 */

#ifndef RBALAMBDAEXPRESSION_HPP
#define RBALAMBDAEXPRESSION_HPP

#include "RBAExpression.hpp"

namespace rba
{

class RBAArbitrator;
class RBAConstraintInfo;
class RBAVariable;
class RBARuleObject;

class DLL_EXPORT RBALambdaExpression : public RBAExpression
{
public:
  RBALambdaExpression()=default;
  RBALambdaExpression(const RBALambdaExpression&)=delete;
  RBALambdaExpression(const RBALambdaExpression&&)=delete;
  RBALambdaExpression& operator=(const RBALambdaExpression&)=delete;
  RBALambdaExpression& operator=(const RBALambdaExpression&&)=delete;
  virtual ~RBALambdaExpression()=default;

public:
  void setX(RBAVariable* const x);
  void setBodyText(RBAExpression* const expr);
  RBAVariable* const getX() const;
  RBAExpression* const getBodyText() const;

  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator* arb) const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitrator* arb) const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                                    RBAArbitrator* arb) const override;

  void setRuleObj(const RBARuleObject* const ruleObj);
  void clearRuleObj();

  // Log
#ifdef RBA_USE_LOG
  void createHierarchy();
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

private:
  // variableは調停処理でsetExpression()を呼び出すため、constにしない。
  RBAVariable* variable_;
  RBAExpression* bodyText_ {nullptr};
  const RBARuleObject* ruleObj_ {nullptr};
};

}

#endif
