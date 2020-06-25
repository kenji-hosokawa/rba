/**
 * 加算クラス定義ファイル
 */

#include "RBAPlusOperator.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAModelElementType
RBAPlusOperator::getModelElementType() const
{
  return RBAModelElementType::PlusOperator;
}

}
