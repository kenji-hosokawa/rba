//
// IsTypeOfクラスヘッダファイル
//

#ifndef RBAISTYPEOFOPERATOR_HPP
#define RBAISTYPEOFOPERATOR_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAIsTypeOfOperator : public RBAOperator
{
 public:
  RBAIsTypeOfOperator()=default;
  RBAIsTypeOfOperator(const RBAIsTypeOfOperator&)=delete;
  RBAIsTypeOfOperator(const RBAIsTypeOfOperator&&)=delete;
  RBAIsTypeOfOperator& operator=(const RBAIsTypeOfOperator&)=delete;
  RBAIsTypeOfOperator& operator=(const RBAIsTypeOfOperator&&)=delete;
  virtual ~RBAIsTypeOfOperator()=default;

 public:
  void setTag(const std::string& tag);
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitrator* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  const std::string getSymbol() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif
 private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::string tagId_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

} /* namespace rba */

#endif /* RBAISTYPEOFOPERATOR_HPP */
