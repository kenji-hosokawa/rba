/**
 * シーンオペレータクラス
 */

#ifndef RBASCENEOPERATOR_HPP
#define RBASCENEOPERATOR_HPP

#include "RBADllExport.hpp"
#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBASceneOperator : public RBAOperator
{
protected:
  RBASceneOperator()=default;
  RBASceneOperator(const RBASceneOperator&)=delete;
  RBASceneOperator(const RBASceneOperator&&)=delete;
  RBASceneOperator& operator=(const RBASceneOperator&)=delete;
  RBASceneOperator& operator=(const RBASceneOperator&&)=delete;
public:
  ~RBASceneOperator()=default;

};

}

#endif
