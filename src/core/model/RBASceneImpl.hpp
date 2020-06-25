/**
 * シーン実装クラスヘッダファイル
 */

#ifndef RBASCENEIMPL_HPP
#define RBASCENEIMPL_HPP

#include <memory>
#include "RBAScene.hpp"
#include "RBARuleObject.hpp"

namespace rba
{

class RBAAbstractProperty;

class RBASceneImpl : public RBAScene, public RBARuleObject
{
public:
  explicit RBASceneImpl(const std::string& name="");
  RBASceneImpl(const RBASceneImpl&)=delete;
  RBASceneImpl(const RBASceneImpl&&)=delete;
  RBASceneImpl& operator=(const RBASceneImpl&)=delete;
  RBASceneImpl& operator=(const RBASceneImpl&&)=delete;
  virtual ~RBASceneImpl()=default;

public:
  std::string getName() const override;
  RBAModelElementType getModelElementType() const override;
  bool isGlobal() const override;
  const std::list<std::string>& getPropertyNames() const override;
  std::int32_t getPropertyValue(const std::string& propertyName) const override;
  const RBARuleObject* getMember(const std::string& memberName) const override;
  const RBAAbstractProperty* getProperty(const std::string& propertyName) const;

  void setGlobal(const bool newGlobal);
  const RBAAbstractProperty* addProperty(const std::string& newName,
                                         std::int32_t newValue);

private:
  bool global_ {false};
  std::list<std::string> propertyNames_; // RBASceneでプロパティ名取得に使用
  std::list<std::unique_ptr<RBAAbstractProperty>> properties_;
  std::unordered_map<std::string, RBAAbstractProperty*> nameToProperty_;
};

}

#endif
