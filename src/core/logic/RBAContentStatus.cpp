//
// コンテントの状態遷移管理クラス
//

#include "RBAContentState.hpp"
#include "RBAContentStatus.hpp"
#include "RBAContentStatusType.hpp"

namespace rba
{

void RBAContentStatus::onRequest()
{
  if ((status_ != RBAContentStatusType::Displayed)
      && (status_ != RBAContentStatusType::StandBy)) {
    status_ = RBAContentStatusType::Undisplayed;
  }
}
void RBAContentStatus::setStatusType(
    const RBAContentStatusType type)
{
  status_ = type;
}
RBAContentStatusType RBAContentStatus::getStatusType() const
{
  return status_;
}
bool RBAContentStatus::isActive() const
{
  return ((status_ != RBAContentStatusType::NoRequest)
      && (status_ != RBAContentStatusType::Canceled));
}

bool RBAContentStatus::isUndisplayed() const
{
  return (status_ == RBAContentStatusType::Undisplayed);
}

bool RBAContentStatus::isDisplayed() const
{
  return (status_ == RBAContentStatusType::Displayed);
}
bool RBAContentStatus::isStandby() const
{
  return (status_ == RBAContentStatusType::StandBy);
}
bool RBAContentStatus::hasBeenCanceled() const
{
  return (status_ == RBAContentStatusType::Canceled);
}
bool RBAContentStatus::hasBeenDisplayed() const
{
  return ((status_ == RBAContentStatusType::Displayed)
      || (status_ == RBAContentStatusType::StandBy));
}
} /* namespace rba */
