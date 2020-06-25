/**
 * ビューアクションクラス定義ファイル
 */

#include "RBAArea.hpp"
#include "RBAViewContent.hpp"
#include "RBAViewContentState.hpp"
#include "RBAViewAction.hpp"
#include "RBAViewMove.hpp"
#include "RBAViewTransition.hpp"

namespace rba {

const RBAArea*
RBAViewAction::getArea() const
{
  return nullptr;
}

const RBAViewContent*
RBAViewAction::getFromContent() const
{
  return nullptr;
}

const RBAViewContent*
RBAViewAction::getToContent() const
{
  return nullptr;
}

const RBAViewContentState*
RBAViewAction::getFromContentState() const
{
  return nullptr;
}

const RBAViewContentState*
RBAViewAction::getToContentState() const
{
  return nullptr;
}

const RBAArea*
RBAViewAction::getFromArea() const
{
  return nullptr;
}

const RBAArea*
RBAViewAction::getToArea() const
{
  return nullptr;
}

const RBAViewContent*
RBAViewAction::getContent() const
{
  // 常に派生クラスの関数がコールされるため、この関数がコールされることはない
  return nullptr;
}

const RBAViewContentState*
RBAViewAction::getContentState() const
{
  // 常に派生クラスの関数がコールされるため、この関数がコールされることはない
  return nullptr;
}

}
