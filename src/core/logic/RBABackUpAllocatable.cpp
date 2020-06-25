/**
 * アロケータブルクラス定義ファイル
 */

#include "RBABackUpAllocatable.hpp"

namespace rba
{

RBABackUpAllocatable::RBABackUpAllocatable(const std::string& name)
  : RBARuleObject{name},
    RBAAllocatable{name}
{
}

}

