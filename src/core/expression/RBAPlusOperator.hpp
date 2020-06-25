/**
 * 加算クラスヘッダファイル
 */

#ifndef RBAPLUSOPERATOR_HPP
#define RBAPLUSOPERATOR_HPP

#include "RBAArithmeticOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAPlusOperator : public RBAArithmeticOperator
{
public:
  RBAPlusOperator()=default;
  RBAPlusOperator(const RBAPlusOperator&)=delete;
  RBAPlusOperator(const RBAPlusOperator&&)=delete;
  RBAPlusOperator& operator=(const RBAPlusOperator&)=delete;
  RBAPlusOperator& operator=(const RBAPlusOperator&&)=delete;
  virtual ~RBAPlusOperator()=default;

public:
  RBAModelElementType getModelElementType() const override;

};

}

#endif
