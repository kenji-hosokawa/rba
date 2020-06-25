/**
 * プロパティオペレータクラス
 */

#ifndef RBAPROPERTYOPERATOR_HPP
#define RBAPROPERTYOPERATOR_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAPropertyOperator : public RBAOperator
{
protected:
  RBAPropertyOperator()=default;
  RBAPropertyOperator(const RBAPropertyOperator&)=delete;
  RBAPropertyOperator(const RBAPropertyOperator&&)=delete;
  RBAPropertyOperator& operator=(const RBAPropertyOperator&)=delete;
  RBAPropertyOperator& operator=(const RBAPropertyOperator&&)=delete;

public:
  virtual ~RBAPropertyOperator()=default;

};

}

#endif
