/**
 * リクエストキュークラス実装ファイル
 */

#include <cstdint>

#include "RBARequestQueMember.hpp"
#include "RBAContentState.hpp"

namespace rba {

RBARequestQueMember::RBARequestQueMember(const RBAContentState* const contentState, const bool isOn,
                                         const std::uint32_t syncIndex):
    contentState_{contentState},
    isOn_{isOn},
    syncIndex_{syncIndex}
{
}

const RBAContentState* RBARequestQueMember::getContentState() const {
  return contentState_;
}

bool RBARequestQueMember::isOn() const {
  return isOn_;
}

std::uint32_t RBARequestQueMember::getSyncIndex() const {
  return syncIndex_;
}

}
