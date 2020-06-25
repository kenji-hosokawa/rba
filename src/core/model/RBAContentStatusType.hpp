//
// コンテントの状態遷移種別
//

#ifndef RBACONTENTSTATUSTYPE_HPP
#define RBACONTENTSTATUSTYPE_HPP

namespace rba
{

enum class RBAContentStatusType : std::uint8_t
{
  NoRequest,
  Undisplayed,
  Displayed,
  StandBy,
  Canceled
};
}

#endif /* RBACONTENTSTATUSTYPE_HPP */
