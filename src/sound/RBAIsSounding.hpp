/**
 * Soundingチェッククラスヘッダファイル
 */

#ifndef RBAISSOUNDING_HPP
#define RBAISSOUNDING_HPP

#include <string>
#include "RBASoundContentOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAIsSounding : public RBASoundContentOperator
{
public:
  RBAIsSounding()=default;
  RBAIsSounding(const RBAIsSounding&)=delete;
  RBAIsSounding(const RBAIsSounding&&)=delete;
  RBAIsSounding& operator=(const RBAIsSounding&)=delete;
  RBAIsSounding& operator=(const RBAIsSounding&&)=delete;
  virtual ~RBAIsSounding()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
