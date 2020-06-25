/**
 * 論理オペレータクラスヘッダファイル
 */

#ifndef RBALOGICOPERATOR_HPP
#define RBALOGICOPERATOR_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBALogicalOperator : public RBAOperator
{
 protected:
  RBALogicalOperator()=default;
  RBALogicalOperator(const RBALogicalOperator&)=delete;
  RBALogicalOperator(const RBALogicalOperator&&)=delete;
  RBALogicalOperator& operator=(const RBALogicalOperator&)=delete;
  RBALogicalOperator& operator=(const RBALogicalOperator&&)=delete;

 public:
  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
