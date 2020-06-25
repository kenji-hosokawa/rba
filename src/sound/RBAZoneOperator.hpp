/**
 * ゾーンオペレータクラスヘッダファイル
 */

#ifndef RBAZONEOPERATOR_HPP
#define RBAZONEOPERATOR_HPP

#include "RBAAllocatableOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAZoneOperator : public RBAAllocatableOperator
{
protected:
  RBAZoneOperator()=default;
  RBAZoneOperator(const RBAZoneOperator&)=delete;
  RBAZoneOperator(const RBAZoneOperator&&)=delete;
  RBAZoneOperator& operator=(const RBAZoneOperator&)=delete;
  RBAZoneOperator& operator=(const RBAZoneOperator&&)=delete;

public:
  virtual ~RBAZoneOperator()=default;

};

}

#endif
