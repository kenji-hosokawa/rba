/**
 * 算術オペレータクラスヘッダファイル
 */

#ifndef RBAARITHMETICOPERATOR_HPP
#define RBAARITHMETICOPERATOR_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAArithmeticOperator : public RBAOperator
{
protected:
  RBAArithmeticOperator()=default;
  RBAArithmeticOperator(const RBAArithmeticOperator&)=delete;
  RBAArithmeticOperator(const RBAArithmeticOperator&&)=delete;
  RBAArithmeticOperator& operator=(const RBAArithmeticOperator&)=delete;
  RBAArithmeticOperator& operator=(const RBAArithmeticOperator&&)=delete;

};

}

#endif
