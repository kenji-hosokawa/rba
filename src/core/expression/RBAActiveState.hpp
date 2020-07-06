//
// activeState header
//

#ifndef RBAACTIVESTATE_HPP
#define RBAACTIVESTATE_HPP

#include "RBAContentOperator.hpp"

namespace rba
{

class RBAActiveState : public RBAContentOperator
{
 public:
  RBAActiveState()=default;
  RBAActiveState(const RBAActiveState&)=delete;
  RBAActiveState(const RBAActiveState&&)=delete;
  RBAActiveState& operator=(const RBAActiveState&)=delete;
  RBAActiveState& operator=(const RBAActiveState&&)=delete;
  virtual ~RBAActiveState()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitrator* arb) const override;
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
#endif
};

} /* namespace rba */

#endif /* RBAACTIVESTATE_HPP */
