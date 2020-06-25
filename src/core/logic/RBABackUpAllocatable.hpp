/**
 * バックアップ用アロケータブルクラスヘッダファイル
 */

#ifndef RBABACKUPALLOCATABLE_HPP
#define RBABACKUPALLOCATABLE_HPP

#include "RBAAllocatable.hpp"

namespace rba
{
class RBABackUpAllocatable : public RBAAllocatable
{
public:
  explicit RBABackUpAllocatable(const std::string& name);
  RBABackUpAllocatable(const RBABackUpAllocatable&)=delete;
  RBABackUpAllocatable(const RBABackUpAllocatable&&)=delete;
  RBABackUpAllocatable& operator=(const RBABackUpAllocatable&)=delete;
  RBABackUpAllocatable& operator=(const RBABackUpAllocatable&&)=delete;
  virtual ~RBABackUpAllocatable()=default;

};

}

#endif
