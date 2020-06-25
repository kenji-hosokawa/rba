/**
 * プロパティ抽象クラス定義ファイル
 */

#include "RBAAbstractProperty.hpp"
#include "RBASceneImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAAbstractProperty::RBAAbstractProperty(const RBASceneImpl* const scene, const std::string& name)
  : RBARuleObject{name},
    scene_{scene}
{
}

RBAModelElementType
RBAAbstractProperty::getModelElementType() const
{
  return RBAModelElementType::Property;
}

const RBASceneImpl*
RBAAbstractProperty::getScene() const
{
  return scene_;
}

}
