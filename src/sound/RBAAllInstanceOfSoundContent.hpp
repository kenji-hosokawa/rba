/**
 * AllInstanceOfSoundContentクラスヘッダファイル
 */

#ifndef RBAALLINSRTANCEOFSOUNDCONTENTIMPL_HPP
#define RBAALLINSRTANCEOFSOUNDCONTENTIMPL_HPP

#include "RBASetExpression.hpp"
#include "RBASoundContentSet.hpp"

namespace rba {

class DLL_EXPORT RBAAllInstanceOfSoundContent : public RBASetExpression
{
public:
  RBAAllInstanceOfSoundContent()=default;
  RBAAllInstanceOfSoundContent(const RBAAllInstanceOfSoundContent&)=delete;
  RBAAllInstanceOfSoundContent(const RBAAllInstanceOfSoundContent&&)=delete;
  RBAAllInstanceOfSoundContent& operator=(const RBAAllInstanceOfSoundContent&)=delete;
  RBAAllInstanceOfSoundContent& operator=(const RBAAllInstanceOfSoundContent&&)=delete;
  virtual ~RBAAllInstanceOfSoundContent()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitrator* arb) const override;
  void setContents(const std::list<const RBASoundContentImpl*>& contents);

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

private:
  RBASoundContentSet allSoundContentSet_;

};

}

#endif
