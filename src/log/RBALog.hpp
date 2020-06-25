/**
 * ログクラス
 */

#ifndef RBALOG_HPP
#define RBALOG_HPP

#include <string>

namespace rba
{

class RBALog
{
public:
  RBALog(const std::int32_t level, const std::string& log);
  RBALog(const RBALog&)=delete;
  RBALog(const RBALog&&)=delete;
  RBALog& operator=(const RBALog&)=delete;
  RBALog& operator=(const RBALog&&)=delete;
  virtual ~RBALog()=default;

public:
  int32_t getLevel() const;
  const std::string& getLog() const;

private:
  int32_t level_;
  std::string log_;

};

}

#endif
