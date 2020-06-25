/**
 * 整数プロパティクラス定義ファイル
 */

#include "RBAIntegerProperty.hpp"
#include "RBASceneImpl.hpp"

namespace rba
{

RBAIntegerProperty::RBAIntegerProperty(const RBASceneImpl* const scene,
                                       const std::string& newName,
                                       const std::int32_t newValue)
  : RBAAbstractProperty{scene, newName},
    value_{newValue}
{
}

std::int32_t
RBAIntegerProperty::getValue() const
{
  return value_;
}

#ifdef RBA_USE_LOG
const std::string
RBAIntegerProperty::getExpressionText() const
{
  return getScene()->getElementName() + "." + getElementName();
}
#endif

}
