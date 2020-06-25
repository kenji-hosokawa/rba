/**
 * 値クラスヘッダファイル
 */

#ifndef RBAVALUEEXPRESSION_HPP
#define RBAVALUEEXPRESSION_HPP

#include "RBAExpression.hpp"

namespace rba
{

class DLL_EXPORT RBAValueExpression : public RBAExpression
{
protected:
  RBAValueExpression()=default;
  RBAValueExpression(const RBAValueExpression&)=delete;
  RBAValueExpression(const RBAValueExpression&&)=delete;
  RBAValueExpression& operator=(const RBAValueExpression&)=delete;
  RBAValueExpression& operator=(const RBAValueExpression&&)=delete;
public:
  virtual ~RBAValueExpression()=default;

};

}

#endif
