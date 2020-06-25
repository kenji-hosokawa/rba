/**
 * セットオペレータクラスヘッダファイル
 */

#ifndef RBASETOPERATOR_HPP
#define RBASETOPERATOR_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBASetOperator : public RBAOperator
{
protected:
  RBASetOperator()=default;
  RBASetOperator(const RBASetOperator&)=delete;
  RBASetOperator(const RBASetOperator&&)=delete;
  RBASetOperator& operator=(const RBASetOperator&)=delete;
  RBASetOperator& operator=(const RBASetOperator&&)=delete;
public:
  virtual ~RBASetOperator()=default;

};

}

#endif
