/**
 * ログコレクターインタフェースクラス
 */

#ifndef RBAILOGCOLLECTOR_HPP
#define RBAILOGCOLLECTOR_HPP

#include <string>
#include "RBADllExport.hpp"

namespace rba
{

class DLL_EXPORT RBAILogCollector
{
protected:
  RBAILogCollector()=default;
  RBAILogCollector(const RBAILogCollector&)=delete;
  RBAILogCollector(const RBAILogCollector&&)=delete;
  RBAILogCollector& operator=(const RBAILogCollector&)=delete;
  RBAILogCollector& operator=(const RBAILogCollector&&)=delete;
  virtual ~RBAILogCollector()=default;

public:
  virtual void log(const std::string& logLine)=0;

};

}

#endif
