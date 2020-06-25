//
// .hasBeenDisplayed()のヘッダーファイル
//

#ifndef RBAHASBEENDISPLAYED_HPP
#define RBAHASBEENDISPLAYED_HPP

#include "RBAContentOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAHasBeenDisplayed : public RBAContentOperator
{
 public:
  RBAHasBeenDisplayed()=default;
  RBAHasBeenDisplayed(const RBAHasBeenDisplayed&)=delete;
  RBAHasBeenDisplayed(const RBAHasBeenDisplayed&&)=delete;
  RBAHasBeenDisplayed& operator=(const RBAHasBeenDisplayed&)=delete;
  RBAHasBeenDisplayed& operator=(const RBAHasBeenDisplayed&&)=delete;
  virtual ~RBAHasBeenDisplayed()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif
};

} /* namespace rba */

#endif /* RBAHASBEENDISPLAYED_HPP */
