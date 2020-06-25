/**
 * シーンコンディションクラスヘッダファイル
 */

#ifndef RBASCENECONDITION_HPP
#define RBASCENECONDITION_HPP

#include "RBAExpression.hpp"

namespace rba
{

class DLL_EXPORT RBASceneCondition : public RBAExpression
{
protected:
  RBASceneCondition()=default;
  RBASceneCondition(const RBASceneCondition&)=delete;
  RBASceneCondition(const RBASceneCondition&&)=delete;
  RBASceneCondition& operator=(const RBASceneCondition&)=delete;
  RBASceneCondition& operator=(const RBASceneCondition&&)=delete;
public:
  virtual ~RBASceneCondition()=default;

};

}

#endif
