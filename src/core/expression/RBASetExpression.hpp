/**
 * セット関数クラスヘッダファイル
 */

#ifndef RBASETEXPRESSION_HPP
#define RBASETEXPRESSION_HPP

#include "RBAExpression.hpp"

namespace rba
{

class DLL_EXPORT RBASetExpression : public RBAExpression
{
protected:
  RBASetExpression()=default;
  RBASetExpression(const RBASetExpression&)=delete;
  RBASetExpression(const RBASetExpression&&)=delete;
  RBASetExpression& operator=(const RBASetExpression&)=delete;
  RBASetExpression& operator=(const RBASetExpression&&)=delete;
public:
  virtual ~RBASetExpression()=default;

};

}

#endif
