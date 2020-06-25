/**
 * 調停要求クラス実装ファイル
 */

#include "RBARequest.hpp"

namespace rba
{

RBARequest::RBARequest(const std::string& context, const bool isOn) :
  context_{context},
  isOn_{isOn}
{
}

std::string
RBARequest::getContext() const
{
  return context_;
}

bool
RBARequest::isOn() const
{
  return isOn_;
}

}
