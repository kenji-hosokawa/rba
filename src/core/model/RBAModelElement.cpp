/**
 * オブジェクトクラス定義ファイル
 */

#include "RBAModelElement.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void RBAModelElement::clearStatus()
{
  // クリアする内部状態がないModelElementからはこの関数がコールされる
  // クリアする内部状態があるModelElementからはoverrideされた関数がコールされる
}
RBAModelElementType
RBAModelElement::getModelElementType() const
{
  // 派生クラスの関数がコールされるため、この関数がコールされることはない
  return RBAModelElementType::None;
}

bool
RBAModelElement::isModelElementType(const RBAModelElementType elemType) const
{
  return (elemType == getModelElementType());
}

}
