/**
 * アロケータブルクラス定義ファイル
 */

#include <algorithm>

#include "RBAAllocatable.hpp"
#include "RBAModelElementType.hpp"
#include "RBAViewContent.hpp"
#include "RBAAreaImpl.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAConstraintMap.hpp"

namespace rba
{

RBAAllocatable::RBAAllocatable(const std::string& name)
  : RBARuleObject{name},
    RBAAbstractAllocatable{name}
{
}

void RBAAllocatable::clearStatus()
{
  allocatablesAffectedByThisAllocatable_.clear();
  state_ = nullptr;
  hiddenChecked_ = false;
  checked_ = false;
  attenuateChecked_ = false;
  hidden_ = false;
  attenuated_ = false;
}

bool
RBAAllocatable::isArea() const
{
  return isModelElementType(RBAModelElementType::Area);
}

bool
RBAAllocatable::isZone() const
{
  return isModelElementType(RBAModelElementType::Zone);
}

RBAArbitrationPolicy
RBAAllocatable::getAllocatableArbitrationPolicy() const
{
  return arbitrationPolicy_;
}

void
RBAAllocatable::setArbitrationPolicy(const RBAArbitrationPolicy newPolicy)
{
  arbitrationPolicy_ = newPolicy;
}

std::int32_t
RBAAllocatable::getVisibility() const
{
  return visibility_;
}

void
RBAAllocatable::setVisibility(const std::int32_t newVisibility)
{
  visibility_ = newVisibility;
}
  
const std::list<const RBAAllocatable*>&
RBAAllocatable::getAllocatablesAffectedByYou() const
{
  return allocatablesAffectedByThisAllocatable_;
}

void
RBAAllocatable::clearAllocatablesAffectedByYou()
{
  return allocatablesAffectedByThisAllocatable_.clear();
}

void
RBAAllocatable::addAllocatableWhichHasBeenAffectedByYou(const RBAAllocatable* const allocatable)
{
  allocatablesAffectedByThisAllocatable_.push_back(allocatable);
}

void
RBAAllocatable::removeAffectAllocatable(const RBAAllocatable* const allocatable)
{
  const auto it = std::find(allocatablesAffectedByThisAllocatable_.begin(),
		      allocatablesAffectedByThisAllocatable_.end(), allocatable);
  if(it != allocatablesAffectedByThisAllocatable_.end()) {
    static_cast<void>(allocatablesAffectedByThisAllocatable_.erase(it));
  }
}

void
RBAAllocatable::clearAffectAllocatable()
{
  allocatablesAffectedByThisAllocatable_.clear();
}

void
RBAAllocatable::clearChecked()
{
  hiddenChecked_ = false;
  checked_ = false;
  attenuateChecked_ =false;
  hidden_ = false;
  attenuated_ = false;
}

std::int32_t
RBAAllocatable::getIndex() const
{
  return index_;
}

void
RBAAllocatable::setIndex(const std::int32_t newIndex)
{
  index_ = newIndex;
}

bool
RBAAllocatable::compare(const RBAAllocatable* const arg0, const RBAAllocatable* const arg1)
{
  const std::int32_t visibility0 {arg0->getVisibility()};
  const std::int32_t visibility1 {arg1->getVisibility()};
  // 前要素が後要素よりも視認性が高いので入れ替えない
  if(visibility0 > visibility1) {
    return true;
  }
  // 前要素と後要素の視認性が同じなのでZオーダーを比較する
  else if(visibility0 == visibility1) {
    std::int32_t zorder0{0};
    std::int32_t zorder1{0};
    if(arg0->isModelElementType(RBAModelElementType::Area)) {
      zorder0 = (dynamic_cast<const RBAAreaImpl*>(arg0))->getZorder();
      zorder1 = (dynamic_cast<const RBAAreaImpl*>(arg1))->getZorder();
    }
    else {
      zorder0 = ZONE_ZORDER;
      zorder1 = ZONE_ZORDER;
    }
    // 前要素が後要素よりもZオーダーが大きいので入れ替えない
    if(zorder0 > zorder1) {
      return true;
    }
    // 前要素と後要素のZオーダーが同じなので入れ替えない
    else if(zorder0 == zorder1) {
      return false;
    }
    // 前要素が後要素よりもZオーダーが小さいので入れ替える
    else {
      return false;
    }
  }
  // 前要素が後要素よりも視認性が低いので入れ替える
  else {
    return false;
  }
}

bool
RBAAllocatable::compareIndex(const RBAAllocatable* const arg0,
			     const RBAAllocatable* const arg1)
{
  return arg0->getIndex() < arg1->getIndex();
}

void
RBAAllocatable::addConstraint(RBAConstraintImpl* const constraint,
                              const RBAConstraintMap& kind)
{
  if (kind == RBAConstraintMap::CONTENT_ALLOCATE_CONSTRAINTS) {
    addConstraintImpl(constraint, constraints_);
  } else if (kind == RBAConstraintMap::HIDDEN_TRUE_CHECK_CONSTRAINTS) {
    addConstraintImpl(constraint, hiddenTrueCheckConstraints_);
  } else if (kind == RBAConstraintMap::HIDDEN_FALSE_CHECK_CONSTRAINTS) {
    addConstraintImpl(constraint, hiddenFalseCheckConstraints_);
  } else if (kind == RBAConstraintMap::ATTENUATE_TRUE_CHECK_CONSTRAINTS) {
    addConstraintImpl(constraint, attenuateTrueCheckConstraints_);
  } else {
    addConstraintImpl(constraint, attenuateFalseCheckConstraints_);
  }
}

std::list<RBAConstraintImpl*>&
RBAAllocatable::getConstraints()
{
  return constraints_;
}
std::list<RBAConstraintImpl*>& RBAAllocatable::getHiddenTrueCheckConstraints()
{
  return hiddenTrueCheckConstraints_;
}
std::list<RBAConstraintImpl*>& RBAAllocatable::getHiddenFalseCheckConstraints()
{
  return hiddenFalseCheckConstraints_;
}
std::list<RBAConstraintImpl*>& RBAAllocatable::getAttenuateTrueCheckConstraints()
{
  return attenuateTrueCheckConstraints_;
}
std::list<RBAConstraintImpl*>& RBAAllocatable::getAttenuateFalseCheckConstraints()
{
  return attenuateFalseCheckConstraints_;
}

bool RBAAllocatable::hasConstraint(const RBAConstraintImpl* const constraint) const
{
  if ((std::find(constraints_.begin(), constraints_.end(), constraint)
      != constraints_.end())
      || (std::find(hiddenTrueCheckConstraints_.begin(),
                    hiddenTrueCheckConstraints_.end(), constraint)
          != hiddenTrueCheckConstraints_.end())
      || (std::find(hiddenFalseCheckConstraints_.begin(),
                    hiddenFalseCheckConstraints_.end(), constraint)
          != hiddenFalseCheckConstraints_.end())
      || (std::find(attenuateTrueCheckConstraints_.begin(),
                    attenuateTrueCheckConstraints_.end(), constraint)
          != attenuateTrueCheckConstraints_.end())
      || (std::find(attenuateFalseCheckConstraints_.begin(),
                    attenuateFalseCheckConstraints_.end(), constraint)
          != attenuateFalseCheckConstraints_.end())) {
    return true;
  }
  return false;
}

bool
RBAAllocatable::isChecked() const
{
  return checked_;
}

void
RBAAllocatable::setChecked(const bool checked)
{
  checked_ = checked;
}

bool
RBAAllocatable::isHiddenChecked() const
{
  return hiddenChecked_;
}

void
RBAAllocatable::setHiddenChecked(const bool hiddenChecked)
{
  hiddenChecked_ = hiddenChecked;
}

bool
RBAAllocatable::isAttenuateChecked() const
{
  return attenuateChecked_;
}

void
RBAAllocatable::setAttenuateChecked(const bool attenuateChecked)
{
  this->attenuateChecked_ = attenuateChecked;
}

bool
RBAAllocatable::isAttenuated() const
{
  return attenuated_;
}

void
RBAAllocatable::setAttenuated(const bool attenuated)
{
  this->attenuated_ = attenuated;
}

bool
RBAAllocatable::isHidden() const
{
  return hidden_;
}

void
RBAAllocatable::setHidden(const bool hidden)
{
  hidden_ = hidden;
}

const RBAContentState*
RBAAllocatable::getState() const
{
  return state_;
}

void
RBAAllocatable::setState(const RBAContentState* const state)
{
  state_ = state;
}

#ifdef RBA_USE_LOG
std::string
RBAAllocatable::getSymbol() const
{
  // 派生クラスの関数がコールされるので、この関数がコールされることはない
  return "Allocatable";
}

std::string
RBAAllocatable::getHiddenSymbol() const
{
  // 派生クラスの関数がコールされるので、この関数がコールされることはない
  return "Allocatable: Unsuppored operation exception";
}

std::string
RBAAllocatable::getArbitrationPolicyString() const
{
  std::string res;
  switch(arbitrationPolicy_) {
  case RBAArbitrationPolicy::FIRST_COME_FIRST:
    res = "FIRST_COME_FIRST";
    break;
  case RBAArbitrationPolicy::LAST_COME_FIRST:
    res = "LAST_COME_FIRST";
    break;
  case RBAArbitrationPolicy::PRIORITY_FIRST_COME_FIRST:
    res = "PRIORITY_FIRST_COME_FIRST";
    break;
  case RBAArbitrationPolicy::PRIORITY_LAST_COME_FIRST:
    res = "PRIORITY_LAST_COME_FIRST";
    break;
  default:
    res = "DEFAULT";
    break;
  }

  return res;
}

std::string
RBAAllocatable::getVisibilityString() const
{
  return std::to_string(visibility_);
}
#endif

void
RBAAllocatable::addConstraintImpl(RBAConstraintImpl* const constraint,
                                  std::list<RBAConstraintImpl*>& constraints)
{
  if (std::find(constraints.begin(), constraints.end(), constraint)
      == constraints.end()) {
    constraints.push_back(constraint);
  }
}

}
