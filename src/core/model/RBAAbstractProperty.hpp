/**
 * プロパティ抽象クラスヘッダファイル
 */

#ifndef RBAABSTRACTPROPERTY_HPP
#define RBAABSTRACTPROPERTY_HPP

#include <cstdint>
#include "RBARuleObject.hpp"

namespace rba
{

class RBASceneImpl;

class RBAAbstractProperty : public RBARuleObject
{
protected:
  RBAAbstractProperty(const RBASceneImpl* const scene, const std::string& name);
  RBAAbstractProperty(const RBAAbstractProperty&)=delete;
  RBAAbstractProperty(const RBAAbstractProperty&&)=delete;
  RBAAbstractProperty& operator=(const RBAAbstractProperty&)=delete;
  RBAAbstractProperty& operator=(const RBAAbstractProperty&&)=delete;

public:
  virtual ~RBAAbstractProperty()=default;

public:
  RBAModelElementType getModelElementType() const override;
  virtual std::int32_t getValue() const=0;
  virtual const RBASceneImpl* getScene() const;

  // Log
#ifdef RBA_USE_LOG
  virtual const std::string getExpressionText() const=0;
#endif

private:
  const RBASceneImpl* scene_;

};

}

#endif
