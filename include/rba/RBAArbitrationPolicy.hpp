// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * 調停ポリシータイプクラス
 */

#ifndef RBAARBITRATIONPOLICY_HPP
#define RBAARBITRATIONPOLICY_HPP

namespace rba
{

/**
 * @cond japanese
 * @enum RBAArbitrationPolicy
 * 調停ポリシーの種類を示す
 * @endcond
 *
 * @cond english
 * @enum RBAArbitrationPolicy
 * Type of arbitration policy.
 * @endcond
 */
enum class RBAArbitrationPolicy : std::uint8_t
{
  /**
   * @cond japanese
   * @brief 優先度後勝ち調停と同義
   * @endcond
   *
   * @cond english
   * @brief Same PRIORITY_LAST_COME_FIRST.
   * @endcond
   */
  DEFAULT,
  /**
   * @cond japanese
   * @brief 先勝ち調停
   * @details 先に発生した要求を優先します
   * @endcond
   *
   * @cond english
   * @brief First Come First Arbitration.
   * @details give priority to first come request.
   * @endcond
   */
  FIRST_COME_FIRST,
  /**
   * @cond japanese
   * @brief 後勝ち調停
   * @details 後から発生した要求を優先します
   * @endcond
   *
   * @cond english
   * @brief Last Come First Arbitration.
   * @details give priority to last come request.
   * @endcond
   */
  LAST_COME_FIRST,
  /**
   * @cond japanese
   * @brief 優先度先勝ち調停
   * @details コンテントに設定した優先度に従います\n
   * 優先度が同じ場合、先に発生した要求を優先します
   * @endcond
   *
   * @cond english
   * @brief Priority and First Come First Arbitration.
   * @details Follow the Priority of Contents.
   * If same priority then give priority to first come request.
   * @endcond
   */
  PRIORITY_FIRST_COME_FIRST,
  /**
   * @cond japanese
   * @brief 優先度後勝ち調停
   * @details コンテントに設定した優先度に従います\n
   * 優先度が同じ場合、後から発生した要求を優先します
   * @endcond
   *
   * @cond english
   * @brief Priority and Last Come First Arbitration.
   * @details Follow the Priority of Contents.
   * If same priority then give priority to last come request.
   * @endcond
   */
  PRIORITY_LAST_COME_FIRST
};

}

#endif
