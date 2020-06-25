/**
 * 調停要求クラスヘッダファイル
 */

#ifndef RBAREQUEST_HPP
#define RBAREQUEST_HPP

#include <string>
#include "RBADllExport.hpp"

namespace rba
{

class DLL_EXPORT RBARequest
{
 public:
  explicit RBARequest(const std::string& context, const bool isOn = true);
  RBARequest(const RBARequest&)=delete;
  RBARequest(const RBARequest&&)=delete;
  RBARequest& operator=(const RBARequest&)=delete;
  RBARequest& operator=(const RBARequest&&)=delete;
  virtual ~RBARequest()=default;

 public:
  std::string getContext() const;
  bool isOn() const;
  
 private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::string context_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  bool isOn_;

};

}

#endif
