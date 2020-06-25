/**
 * 含意オペレータクラスヘッダファイル
 */

#ifndef RBAIMPLIESOPERATOR_HPP
#define RBAIMPLIESOPERATOR_HPP

#include "RBALogicalOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAImpliesOperator: public RBALogicalOperator
{
public:
  RBAImpliesOperator()=default;
  RBAImpliesOperator(const RBAImpliesOperator&)=delete;
  RBAImpliesOperator(const RBAImpliesOperator&&)=delete;
  RBAImpliesOperator& operator=(const RBAImpliesOperator&)=delete;
  RBAImpliesOperator& operator=(const RBAImpliesOperator&&)=delete;
  virtual ~RBAImpliesOperator()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  void createHierarchy() override;
#endif

};

}

#endif
