/**
 * ゾーンの全インスタンスクラス
 */

#ifndef RBAALLINSTANCEOFZONE_HPP
#define RBAALLINSTANCEOFZONE_HPP

#include "RBASetExpression.hpp"
#include "RBAZoneSet.hpp"

namespace rba
{

class DLL_EXPORT RBAAllInstanceOfZone : public RBASetExpression
{
public:
  RBAAllInstanceOfZone()=default;
  RBAAllInstanceOfZone(const RBAAllInstanceOfZone&)=delete;
  RBAAllInstanceOfZone(const RBAAllInstanceOfZone&&)=delete;
  RBAAllInstanceOfZone& operator=(const RBAAllInstanceOfZone&)=delete;
  RBAAllInstanceOfZone& operator=(const RBAAllInstanceOfZone&&)=delete;
  virtual ~RBAAllInstanceOfZone()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitrator* arb) const override;
  void setZones(const std::list<const RBAZoneImpl*> zones);

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

private:
  RBAZoneSet allZoneSet_;

};

}

#endif
