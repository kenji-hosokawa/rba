/**
 * アロケータブル取得クラスヘッダファイル
 */

#ifndef RBAGETALLOCATABLES_HPP
#define RBAGETALLOCATABLES_HPP

#include "RBAContentOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAGetAllocatables : public RBAContentOperator
{
public:
  RBAGetAllocatables()=default;
  RBAGetAllocatables(const RBAGetAllocatables&)=delete;
  RBAGetAllocatables(const RBAGetAllocatables&&)=delete;
  RBAGetAllocatables& operator=(const RBAGetAllocatables&)=delete;
  RBAGetAllocatables& operator=(const RBAGetAllocatables&&)=delete;
  virtual ~RBAGetAllocatables()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitrator* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  void createHierarchy() override;
#endif

};

}

#endif
