/**
 * 整数プロパティクラス
 */

#ifndef RBAINTEGERPROPERTY_HPP
#define RBAINTEGERPROPERTY_HPP

#include "RBAAbstractProperty.hpp"

namespace rba
{

class RBAIntegerProperty : public RBAAbstractProperty
{
public:
  RBAIntegerProperty(const RBASceneImpl* const scene,
                     const std::string& newName, const std::int32_t newValue);
  RBAIntegerProperty(const RBAIntegerProperty&)=delete;
  RBAIntegerProperty(const RBAIntegerProperty&&)=delete;
  RBAIntegerProperty& operator=(const RBAIntegerProperty&)=delete;
  RBAIntegerProperty& operator=(const RBAIntegerProperty&&)=delete;

public:
  std::int32_t getValue() const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
#endif

private:
  std::int32_t value_;

};

}

#endif
