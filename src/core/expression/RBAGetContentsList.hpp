/**
 * コンテントリスト取得クラスヘッダファイル
 */

#ifndef RBAGETCONTENTSLIST_HPP
#define RBAGETCONTENTSLIST_HPP

#include "RBAAllocatableOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAGetContentsList : public RBAAllocatableOperator
{
public:
  RBAGetContentsList()=default;
  RBAGetContentsList(const RBAGetContentsList&)=delete;
  RBAGetContentsList(const RBAGetContentsList&&)=delete;
  RBAGetContentsList& operator=(const RBAGetContentsList&)=delete;
  RBAGetContentsList& operator=(const RBAGetContentsList&&)=delete;
  virtual ~RBAGetContentsList()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitrator* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  void createHierarchy() override;
#endif

};

}

#endif
