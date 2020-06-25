//
// ActiveContentsオペレータ
//

#ifndef RBAACTIVECONTENTS_HPP
#define RBAACTIVECONTENTS_HPP

#include "RBAAllocatableOperator.hpp"
#include "RBAContentSet.hpp"

namespace rba
{

class RBAActiveContents : public RBAAllocatableOperator
{
 public:
  RBAActiveContents();
  RBAActiveContents(const RBAActiveContents&)=delete;
  RBAActiveContents(const RBAActiveContents&&)=delete;
  RBAActiveContents& operator=(const RBAActiveContents&)=delete;
  RBAActiveContents& operator=(const RBAActiveContents&&)=delete;
  virtual ~RBAActiveContents()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitrator* arb) const override;

#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
#endif
 private:
  std::unique_ptr<RBAContentSet> contentSet_;
};

}

#endif
