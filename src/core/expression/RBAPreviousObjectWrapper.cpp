/**
 * RuleObjectのPrevious Wrapperクラス定義ファイル
 */
#include "RBAPreviousObjectWrapper.hpp"

namespace rba
{

bool
RBAPreviousObjectWrapper::isPrevious() const
{
  return true;
}

const RBARuleObject*
RBAPreviousObjectWrapper::getRawObject() const
{
  return refObject_->getRawObject();
}

void
RBAPreviousObjectWrapper::setRefObject(const RBARuleObject* const obj)
{
  refObject_ = obj;
}

}
