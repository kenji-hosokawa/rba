/**
 * 表示コンテントオペレータクラス
 */

#ifndef RBAVIEWCONTENTOPERATOR_HPP
#define RBAVIEWCONTENTOPERATOR_HPP

#include "RBAContentOperator.hpp"

namespace rba
{

class RBAViewContentImpl;

class DLL_EXPORT RBAViewContentOperator : public RBAContentOperator
{
protected:
  RBAViewContentOperator()=default;
  RBAViewContentOperator(const RBAViewContentOperator&)=delete;
  RBAViewContentOperator(const RBAViewContentOperator&&)=delete;
  RBAViewContentOperator& operator=(const RBAViewContentOperator&)=delete;
  RBAViewContentOperator& operator=(const RBAViewContentOperator&&)=delete;

public:

};

}

#endif
