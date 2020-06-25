/**
 * プロパティ取得クラス
 */

#ifndef RBAGETPROPERTY_HPP
#define RBAGETPROPERTY_HPP

#include "RBAPropertyOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAGetProperty : public RBAPropertyOperator
{
public:
  RBAGetProperty()=default;
  RBAGetProperty(const RBAGetProperty&)=delete;
  RBAGetProperty(const RBAGetProperty&&)=delete;
  RBAGetProperty& operator=(const RBAGetProperty&)=delete;
  RBAGetProperty& operator=(const RBAGetProperty&&)=delete;
  virtual ~RBAGetProperty()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                                    RBAArbitrator * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
