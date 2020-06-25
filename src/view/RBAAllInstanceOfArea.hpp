/**
 * AllInstanceOfAreaクラスヘッダファイル
 */

#ifndef RBAAllInstanceOfArea_HPP
#define RBAAllInstanceOfArea_HPP

#include "RBAAreaSet.hpp"
#include "RBASetExpression.hpp"

namespace rba
{
class DLL_EXPORT RBAAllInstanceOfArea : public RBASetExpression
{
 public:
  RBAAllInstanceOfArea()=default;
  RBAAllInstanceOfArea(const RBAAllInstanceOfArea&)=delete;
  RBAAllInstanceOfArea(const RBAAllInstanceOfArea&&)=delete;
  RBAAllInstanceOfArea& operator=(const RBAAllInstanceOfArea&)=delete;
  RBAAllInstanceOfArea& operator=(const RBAAllInstanceOfArea&&)=delete;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                        RBAArbitrator* arb) const override;
  void setAreas(const std::list<const RBAAreaImpl*>& areas);

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

 private:
  RBAAreaSet allAreaSet_;
};

}

#endif
