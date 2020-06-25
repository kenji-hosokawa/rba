//
// RBAAllwaysCheckConstraintCollector.hpp
//

#ifndef RBAALLWAYSCHECKCONSTRAINTSETTER_HPP
#define RBAALLWAYSCHECKCONSTRAINTSETTER_HPP

#include "RBAAbstractCollector.hpp"

namespace rba
{
class RBAConstraintImpl;

class RBAAllwaysCheckConstraintCollector : public RBAAbstractCollector
{
 public:
  RBAAllwaysCheckConstraintCollector(RBAModelImpl* const model);
  RBAAllwaysCheckConstraintCollector(const RBAAllwaysCheckConstraintCollector&)=default;
  RBAAllwaysCheckConstraintCollector(RBAAllwaysCheckConstraintCollector&&)=default;
  RBAAllwaysCheckConstraintCollector& operator=(const RBAAllwaysCheckConstraintCollector&)=default;
  RBAAllwaysCheckConstraintCollector& operator=(RBAAllwaysCheckConstraintCollector&&)=default;
  virtual ~RBAAllwaysCheckConstraintCollector()=default;
  void init(const RBAConstraintImpl* const constraint);
  bool isAllways() const;
  void visit(RBAPreviousModifier& exp) final;
 private:
  // 探索中の制約式
  const RBAConstraintImpl* constraint_ {nullptr};
  // 探索中の制約式が常に調停する必要がある制約式であればtrue
  bool isAllways_ {false};
};

} /* namespace rba */

#endif /* RBAALLWAYSCHECKCONSTRAINTSETTER_HPP */
