/**
 * シーン実装クラス定義ファイル
 */

#include "RBASceneImpl.hpp"
#include "RBAModelElementType.hpp"
#include "RBAAbstractProperty.hpp"
#include "RBAIntegerProperty.hpp"

namespace rba
{

RBASceneImpl::RBASceneImpl(const std::string& name)
  : RBAScene(),
    RBARuleObject{name}
{
}

std::string
RBASceneImpl::getName() const
{
  return RBARuleObject::getElementName();
}

RBAModelElementType
RBASceneImpl::getModelElementType() const
{
  return RBAModelElementType::Scene;
}

bool
RBASceneImpl::isGlobal() const
{
  return global_;
}

const std::list<std::string>&
RBASceneImpl::getPropertyNames() const
{
  return propertyNames_;
}

std::int32_t
RBASceneImpl::getPropertyValue(const std::string& propertyName) const
{
  const RBAAbstractProperty* const prop {getProperty(propertyName)};
  if(prop == nullptr) {
    // 未登録のプロパティならば-1を返す
    return -1;
  }

  // デフォルト値を返す
  return prop->getValue();
}

const RBARuleObject* RBASceneImpl::getMember(const std::string& memberName) const
{
  return getProperty(memberName);
}

const RBAAbstractProperty*
RBASceneImpl::getProperty(const std::string& propertyName) const
{
  auto p = nameToProperty_.find(propertyName);
  if(p == nameToProperty_.end()) {
    // 未登録のプロパティならばnullptrを返す
    return nullptr;
  }

  return p->second;
}

void
RBASceneImpl::setGlobal(const bool newGlobal)
{
  global_ = newGlobal;
}

const RBAAbstractProperty*
RBASceneImpl::addProperty(const std::string& newName, std::int32_t newValue)
{
  auto p = nameToProperty_.find(newName);
  if(p != nameToProperty_.end()) {
    // 登録済みのプロパティならば何もしない
    return p->second;
  }

  // 登録
  properties_.push_back(std::make_unique<RBAIntegerProperty>(this,
                                                             newName,
                                                             newValue));
  propertyNames_.push_back(newName);
  nameToProperty_[newName] = properties_.back().get();

  return properties_.back().get();
}

}
