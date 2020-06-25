/**
 * ディスプレイングコンテントクラスヘッダファイル
 */

#ifndef RBADISPLAYINGCONTENT_HPP
#define RBADISPLAYINGCONTENT_HPP

#include <string>
#include "RBAAreaOperator.hpp"

namespace rba
{

class DLL_EXPORT RBADisplayingContent : public RBAAreaOperator
{
public:
  RBADisplayingContent()=default;
  RBADisplayingContent(const RBADisplayingContent&)=delete;
  RBADisplayingContent(const RBADisplayingContent&&)=delete;
  RBADisplayingContent& operator=(const RBADisplayingContent&)=delete;
  RBADisplayingContent& operator=(const RBADisplayingContent&&)=delete;
  virtual ~RBADisplayingContent()=default;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitrator* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
