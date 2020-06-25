/// ステート値クラスヘッダファイル

#ifndef RBASTATEVALUE_HPP
#define RBASTATEVALUE_HPP

#include <cstdint>
#include "RBAContentOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAStateValue : public RBAContentOperator
{
public:
  RBAStateValue()=default;
  RBAStateValue(const RBAStateValue&)=delete;
  RBAStateValue(RBAStateValue&&)=delete;
  RBAStateValue& operator=(const RBAStateValue&)=delete;
  RBAStateValue& operator=(RBAStateValue&&)=delete;
  virtual ~RBAStateValue()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                            RBAArbitrator* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
#endif

};

}

#endif
