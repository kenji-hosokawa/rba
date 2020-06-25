/**
 * セットオブオペレータクラスヘッダファイル
 */

#ifndef RBASETOFOPERATOR_HPP
#define RBASETOFOPERATOR_HPP

#include <memory>
#include "RBAOperator.hpp"

namespace rba
{

class RBAAllocatableSet;
class RBAContentSet;

class DLL_EXPORT RBASetOfOperator : public RBAOperator
{
public:
  RBASetOfOperator();
  RBASetOfOperator(const RBASetOfOperator&)=delete;
  RBASetOfOperator(const RBASetOfOperator&&)=delete;
  RBASetOfOperator& operator=(const RBASetOfOperator&)=delete;
  RBASetOfOperator& operator=(const RBASetOfOperator&&)=delete;
  virtual ~RBASetOfOperator()=default;
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

protected:
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitrator* arb) const override;
  void doActionCore(RBAConstraintInfo* info, RBAArbitrator* arb) override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unique_ptr<RBAAllocatableSet> allocatableSet_;
  std::unique_ptr<RBAContentSet> contentSet_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
