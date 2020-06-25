/**
 *  表示コンテントステートクラス定義ファイル
 */

#include "RBAViewContentState.hpp"

namespace rba
{

std::string
RBAViewContentState::getContentNameByContext(const std::string& context)
{
  return context.substr(0U, context.find(CONTEXT_SEPARATER));
}

std::string
RBAViewContentState::getContentStateNameByContext(const std::string& context)
{
  const std::string::size_type pos {context.find(CONTEXT_SEPARATER)};
  if(pos == std::string::npos) {
    // セパレータ文字が含まれていなければ空文字列を返す
    return "";
  }
  else {
    return context.substr(pos+1U, context.length()-1U);
  }
}

bool
RBAViewContentState::isUniqueName(const std::string& context)
{
  return (context.find(CONTEXT_SEPARATER) != std::string::npos);
}

}
