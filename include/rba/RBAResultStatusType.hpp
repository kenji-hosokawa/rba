// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * 調停結果ステータスタイプクラス
 */

#ifndef RBARESULTSTATUSTYPE_HPP
#define RBARESULTSTATUSTYPE_HPP

namespace rba
{

/**
 * @cond japanese
 * @enum RBAResultStatusType
 * 調停結果の状態を示す
 * @endcond
 *
 * @cond english
 * @enum RBAResultStatusType
 * Status of the arbitration result.
 * @endcond
 */
enum class RBAResultStatusType : std::uint8_t
{
  /**
   * @cond japanese
   * @brief 成功
   * @endcond
   *
   * @cond english
   * @brief Success
   * @endcond
   */
  SUCCESS,

  /**
   * @cond japanese
   * @brief 失敗
   * @endcond
   *
   * @cond english
   * @brief Failed
   * @endcond
   */
  FAILED,

  /**
   * @cond japanese
   * @brief コンテント状態（コンテキスト）が見つからない
   * @endcond
   *
   * @cond english
   * @brief Unknown context or content state
   * @endcond
   */
  UNKNOWN_CONTENT_STATE,

  /**
   * @cond japanese
   * @brief 調停処理差し戻しエラー
   * @endcond
   *
   * @cond english
   * @brief Cancel arbitration error
   * @endcond
   */
  CANCEL_ERROR

};

}

#endif
