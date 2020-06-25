/**
 * エリアオペレータクラスヘッダファイル
 */

#ifndef RBAAREAOPERATOR_HPP
#define RBAAREAOPERATOR_HPP

#include "RBAAllocatableOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAAreaOperator : public RBAAllocatableOperator
{
public:
  RBAAreaOperator()=default;
  RBAAreaOperator(const RBAAreaOperator&)=delete;
  RBAAreaOperator(const RBAAreaOperator&&)=delete;
  RBAAreaOperator& operator=(const RBAAreaOperator&)=delete;
  RBAAreaOperator& operator=(const RBAAreaOperator&&)=delete;
  ~RBAAreaOperator()=default;
};

}

#endif
