/**
 * 整数値クラス
 */

#ifndef RBAINTEGERVALUE_HPP
#define RBAINTEGERVALUE_HPP

#include "RBAValueExpression.hpp"

namespace rba
{

class DLL_EXPORT RBAIntegerValue : public RBAValueExpression
{
public:
  RBAIntegerValue()=default;
  RBAIntegerValue(const RBAIntegerValue&)=delete;
  RBAIntegerValue(const RBAIntegerValue&&)=delete;
  RBAIntegerValue& operator=(const RBAIntegerValue&)=delete;
  RBAIntegerValue& operator=(const RBAIntegerValue&&)=delete;
  virtual ~RBAIntegerValue()=default;

public:
  void setValue(const std::int32_t value);

  std::int32_t getValue() const;
  RBAModelElementType getModelElementType() const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                                    RBAArbitrator * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

 private:
  std::int32_t value_ {0};

};

}

#endif
