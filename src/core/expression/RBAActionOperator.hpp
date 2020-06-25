/**
 * アクションオペレータクラス
 */

#ifndef RBAACTIONOPERATOR_HPP
#define RBAACTIONOPERATOR_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAActionOperator : public RBAOperator
{
protected:
  RBAActionOperator()=default;
  RBAActionOperator(const RBAActionOperator&)=delete;
  RBAActionOperator(const RBAActionOperator&&)=delete;
  RBAActionOperator& operator=(const RBAActionOperator&)=delete;
  RBAActionOperator& operator=(const RBAActionOperator&&)=delete;

public:
  // Log
#ifdef RBA_USE_LOG
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
