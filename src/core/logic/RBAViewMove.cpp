/**
 * RBAViewMove.cpp
 */

#include "RBAArea.hpp"
#include "RBAViewContent.hpp"
#include "RBAViewContentState.hpp"
#include "RBAViewMove.hpp"

namespace rba {

RBAViewMove::RBAViewMove(const RBAArea* const newFromArea, const RBAArea* const newToArea,
			 const RBAViewContentState* const newContentState)
  : RBAViewAction{}
{
  fromArea_ = newFromArea;
  toArea_ = newToArea;
  contentState_ = newContentState;
}

RBAViewMove::RBAViewMove(const RBAViewMove& viewMove)
  : RBAViewAction{viewMove}
{
  fromArea_ = viewMove.fromArea_;
  toArea_ = viewMove.toArea_;
  contentState_ = viewMove.contentState_;
}

bool
RBAViewMove::operator==(const RBAViewAction& viewAction)
{
  if(getViewActionType() != viewAction.getViewActionType()) {
    // ビューアクションタイプが一致しないなら不一致
    return false;
  }

  const RBAViewMove* const viewMove {dynamic_cast<const RBAViewMove*>(&viewAction)};
  return ((fromArea_ == viewMove->fromArea_) &&
          (toArea_ == viewMove->toArea_) &&
          (contentState_ == viewMove->contentState_));
}

const RBAArea*
RBAViewMove::getFromArea() const
{
  return fromArea_;
}

const RBAArea*
RBAViewMove::getToArea() const
{
  return toArea_;
}

const RBAViewContent*
RBAViewMove::getContent() const
{
  return contentState_->getOwner();
}

const RBAViewContentState*
RBAViewMove::getContentState() const
{
  return contentState_;
}

RBAViewActionType
RBAViewMove::getViewActionType() const
{
  return RBAViewActionType::MOVE;
}

}
