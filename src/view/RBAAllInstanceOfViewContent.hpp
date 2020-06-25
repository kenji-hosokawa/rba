/**
 * AllInstanceOfViewContentクラスヘッダファイル
 */

#ifndef RBAALLINSRTANCEOFVIEWCONTENTIMPL_HPP
#define RBAALLINSRTANCEOFVIEWCONTENTIMPL_HPP

#include "RBASetExpression.hpp"
#include "RBAViewContentSet.hpp"

namespace rba
{

class DLL_EXPORT RBAAllInstanceOfViewContent : public RBASetExpression
{
public:
  RBAAllInstanceOfViewContent()=default;
  RBAAllInstanceOfViewContent(const RBAAllInstanceOfViewContent&)=delete;
  RBAAllInstanceOfViewContent(const RBAAllInstanceOfViewContent&&)=delete;
  RBAAllInstanceOfViewContent& operator=(const RBAAllInstanceOfViewContent&)=delete;
  RBAAllInstanceOfViewContent& operator=(const RBAAllInstanceOfViewContent&&)=delete;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitrator* arb) const override;
  void setContents(const std::list<const RBAViewContentImpl*>& contents);

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

private:
  RBAViewContentSet allViewContentSet_;

};

}

#endif
