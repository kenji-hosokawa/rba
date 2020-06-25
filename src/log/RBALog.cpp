/**
 * ログクラス定義ファイル
 */

#include "RBALog.hpp"

namespace rba {

RBALog::RBALog(const std::int32_t level, const std::string& log)
  : level_{level}
  , log_{log}
{
}

int32_t
RBALog::getLevel() const
{
  return level_;
}

const std::string&
RBALog::getLog() const
{
  return log_;
}

}
