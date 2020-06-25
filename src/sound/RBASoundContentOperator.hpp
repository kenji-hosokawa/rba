/**
 * 音声コンテントオペレータクラス
 */

#ifndef RBASOUNDCONTENTOPERATOR_HPP
#define RBASOUNDCONTENTOPERATOR_HPP

#include "RBAContentOperator.hpp"

namespace rba
{

class RBASoundContentImpl;

class DLL_EXPORT RBASoundContentOperator : public RBAContentOperator
{
protected:
  RBASoundContentOperator()=default;
  RBASoundContentOperator(const RBASoundContentOperator&)=delete;
  RBASoundContentOperator(const RBASoundContentOperator&&)=delete;
  RBASoundContentOperator& operator=(const RBASoundContentOperator&)=delete;
  RBASoundContentOperator& operator=(const RBASoundContentOperator&&)=delete;

public:

};

}

#endif
