// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * グッドルーザータイプクラス
 */

#ifndef RBACONTENTLOSERTYPE_HPP
#define RBACONTENTLOSERTYPE_HPP

namespace rba
{

/**
 * @cond japanese
 * @enum RBAContentLoserType
 * コンテントが調停負けした場合の振る舞いのタイプ
 * @endcond
 *
 * @cond english
 * @enum RBAContentLoserType
 * Type of behavior when content loses the arbitration
 * @endcond
 */
enum class RBAContentLoserType : std::uint8_t
{
  /**
   * @cond japanese
   * @brief 調停負けしたら要求を取り下げ
   * @endcond
   *
   * @cond english
   * @brief Always cancels its request when losing arbitration.
   * @endcond
   */
  GOOD_LOSER=0,

  /**
   * @cond japanese
   * @brief 表示状態から非表示状態になったら要求を取り下げる
   * @endcond
   *
   * @cond english
   * @brief Cancels its request only if it lost the arbitration in the displaying state.
   * @endcond
   */
  DO_NOT_GIVEUP_UNTIL_WIN,

  /**
   * @cond japanese
   * @brief 要求を取り下げない
   * @endcond
   *
   * @cond english
   * @brief Never cancels its request.
   * @endcond
   */
  NEVER_GIVEUP
};

}

#endif
