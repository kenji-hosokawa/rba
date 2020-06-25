/**
 * Ifステートメントクラスヘッダファイル
 */

#ifndef RBAIFSTATEMENT_HPP
#define RBAIFSTATEMENT_HPP

#include "RBAExpression.hpp"

namespace rba
{

class DLL_EXPORT RBAIfStatement : public RBAExpression
{
public:
  RBAIfStatement()=default;
  RBAIfStatement(const RBAIfStatement&)=delete;
  RBAIfStatement(const RBAIfStatement&&)=delete;
  RBAIfStatement& operator=(const RBAIfStatement&)=delete;
  RBAIfStatement& operator=(const RBAIfStatement&&)=delete;
  virtual ~RBAIfStatement()=default;

public:
  void setCondition(RBAExpression* const expr);
  void setThenExpression(RBAExpression* const expr);
  void setElseExpression(RBAExpression* const expr);
  RBAExpression* const getCondition() const;
  RBAExpression* const getThenExpression() const;
  RBAExpression* const getElseExpression() const;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator* arb) const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitrator* arb) const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                                    RBAArbitrator* arb) const override;
  void doActionCore(RBAConstraintInfo* info, RBAArbitrator* arb) override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

 private:
  RBAExpression* condition_ {nullptr};
  RBAExpression* thenExpression_ {nullptr};
  RBAExpression* elseExpression_ {nullptr};

};

}

#endif
