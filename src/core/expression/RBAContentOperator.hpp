/**
 * コンテントオペレータクラス
 */

#ifndef RBACONTENTOPERATOR_HPP
#define RBACONTENTOPERATOR_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAContentOperator : public RBAOperator
{
protected:
  RBAContentOperator()=default;
  RBAContentOperator(const RBAContentOperator&)=delete;
  RBAContentOperator(const RBAContentOperator&&)=delete;
  RBAContentOperator& operator=(const RBAContentOperator&)=delete;
  RBAContentOperator& operator=(const RBAContentOperator&&)=delete;

public:
  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

};

}

#endif
