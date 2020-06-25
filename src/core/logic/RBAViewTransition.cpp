/**
 * RBAViewTransition.cpp
 */

#include "RBAArea.hpp"
#include "RBAViewContent.hpp"
#include "RBAViewContentState.hpp"
#include "RBAViewTransition.hpp"

namespace rba {

RBAViewTransition::RBAViewTransition(
    const RBAViewActionType newViewActionType, const RBAArea* const newArea,
    const RBAViewContentState* const newContentState1,
    const RBAViewContentState* const newContentState2)
    : RBAViewAction(),
      viewActionType_{newViewActionType},
      area_{newArea},
      contentState1_{newContentState1},
      contentState2_{newContentState2}
{
}

RBAViewTransition::RBAViewTransition(const RBAViewTransition& viewTrans)
  : RBAViewAction{viewTrans}
{
  viewActionType_ = viewTrans.viewActionType_;
  area_ = viewTrans.area_;
  contentState1_ = viewTrans.contentState1_;
  contentState2_ = viewTrans.contentState2_;
}

bool
RBAViewTransition::operator==(const RBAViewAction& viewAction)
{
  if(getViewActionType() != viewAction.getViewActionType()) {
    // ビューアクションタイプが一致しないなら不一致
    return false;
  }

  const RBAViewTransition* const viewTran
    {dynamic_cast<const RBAViewTransition*>(&viewAction)};
  return ((area_ == viewTran->area_) &&
          (contentState1_ == viewTran->contentState1_) &&
          (contentState2_ == viewTran->contentState2_));
}

const RBAArea*
RBAViewTransition::getArea() const
{
  return area_;
}

const RBAViewContent*
RBAViewTransition::getFromContent() const
{
  if((contentState1_ == nullptr) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_ADD) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_REMOVE)) {
    return nullptr;
  }
  return contentState1_->getOwner();
}

const RBAViewContent*
RBAViewTransition::getToContent() const
{
  if((contentState2_ == nullptr) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_ADD) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_REMOVE)) {
    return nullptr;
  }
  return contentState2_->getOwner();
}

const RBAViewContentState*
RBAViewTransition::getFromContentState() const
{
  if((viewActionType_ == RBAViewActionType::TRANSITION_ADD) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_REMOVE)) {
    return nullptr;
  }
  return contentState1_;
}
  
const RBAViewContentState*
RBAViewTransition::getToContentState() const
{
  if((viewActionType_ == RBAViewActionType::TRANSITION_ADD) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_REMOVE)) {
    return nullptr;
  }
  return contentState2_;
}

const RBAViewContent*
RBAViewTransition::getContent() const
{
  if((contentState1_ == nullptr) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_REPLACE)) {
    return nullptr;
  }
  return contentState1_->getOwner();
}

const RBAViewContentState*
RBAViewTransition::getContentState() const
{
  if(viewActionType_ == RBAViewActionType::TRANSITION_REPLACE) {
    return nullptr;
  }
  return contentState1_;
}

RBAViewActionType
RBAViewTransition::getViewActionType() const
{
  return viewActionType_;
}

}
