/**
 * 名前要素クラスヘッダファイル
 */

#include "RBANamedElement.hpp"

namespace rba
{

RBANamedElement::RBANamedElement(const std::string& newName)
    : RBAModelElement(),
      name_(newName)
{
}

std::string
RBANamedElement::getUniqueName() const
{
  return getElementName();
}

const std::string&
RBANamedElement::getElementName() const
{
  return name_;
}

const std::string&
RBANamedElement::getDynamicName() const
{
  return dynamic_name_;
}

void
RBANamedElement::setDynamicName(const std::string& newName)
{
  dynamic_name_ = newName;
}
}
