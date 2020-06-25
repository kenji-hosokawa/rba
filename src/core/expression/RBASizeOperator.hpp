//
// Sizeオペレータヘッダーファイル
//

#ifndef RBASIZEOPERATOR_HPP
#define RBASIZEOPERATOR_HPP

#include "RBASetOperator.hpp"

namespace rba
{

class RBASizeOperator : public RBASetOperator
{
 public:
  RBASizeOperator()=default;
  RBASizeOperator(const RBASizeOperator&)=delete;
  RBASizeOperator(const RBASizeOperator&&)=delete;
  RBASizeOperator& operator=(const RBASizeOperator&)=delete;
  RBASizeOperator& operator=(const RBASizeOperator&&)=delete;
  virtual ~RBASizeOperator()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  std::int32_t getValueCore(RBAConstraintInfo* info, RBAArbitrator* arb) const override;
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif
};

} /* namespace rba */

#endif /* SRC_CORE_EXPRESSION_RBASIZEOPERATOR_HPP_ */
