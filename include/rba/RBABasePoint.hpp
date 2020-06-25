// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * ベースポイントクラス
 */

#ifndef RBABASEPOINT_HPP
#define RBABASEPOINT_HPP

namespace rba
{

/**
 * @cond japanese
 * @enum RBABasePoint
 * エリアなどサイズを持つオブジェクトの原点位置を示す
 * @endcond
 *
 * @cond english
 * @enum RBABasePoint
 * Base point for object having size. For example Area.
 * @endcond
 */
enum class RBABasePoint : std::uint8_t
{
  /**
   * @cond japanese
   * @brief 左上を起点としてx, yを定義
   * 矩形は(x, y)-(x+width, y+height)
   * @endcond
   *
   * @cond english
   * @brief Defines Left-Top coordinate as the base point of (x, y)
   * The rectangle is represented by (x, y)-(x+width, y+height)
   * @endcond
   */
  LEFT_TOP,

  /**
   * @cond japanese
   * @brief 左中央を起点としてx, yを定義
   * 矩形は(x, y-height/2)-(x+width, y+height/2)
   * @endcond
   *
   * @cond english
   * @brief Defines Left-Middle coordinate as the base point of (x, y)
   * The rectangle is represented by (x, y-height/2)-(x+width, y+height/2)
   * @endcond
   */
  LEFT_MIDDLE,

  /**
   * @cond japanese
   * @brief 左下を起点としてx, yを定義
   * 矩形は(x, y-height)-(x+width, y)
   * @endcond
   *
   * @cond english
   * @brief Defines Left-Bottom coordinate as the base point of (x, y)
   * The rectangle is represented by (x, y-height)-(x+width, y)
   * @endcond
   */
  LEFT_BOTTOM,

  /**
   * @cond japanese
   * @brief 右上を起点としてx, yを定義
   * 矩形は(x-width, y)-(x, y+height)
   * @endcond
   *
   * @cond english
   * @brief Defines Right-Top coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width, y)-(x, y+height)
   * @endcond
   */
  RIGHT_TOP,

  /**
   * @cond japanese
   * @brief 右中央を起点としてx, yを定義
   * 矩形は(x-width, y-height/2)-(x, y+height/2)
   * @endcond
   *
   * @cond english
   * @brief Defines Right-Middle coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width, y-height/2)-(x, y+height/2)
   * @endcond
   */
  RIGHT_MIDDLE,

  /**
   * @cond japanese
   * @brief 右下を起点としてx, yを定義
   * 矩形は(x-width, y-height)-(x, y)
   * @endcond
   *
   * @cond english
   * @brief Defines Right-Bottom coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width, y-height)-(x, y)
   * @endcond
   */
  RIGHT_BOTTOM,

  /**
   * @cond japanese
   * @brief 中央上を起点としてx, yを定義
   * 矩形は(x-width/2, y)-(x+width/2, y+height)
   * @endcond
   *
   * @cond english
   * @brief Defines Center-Top coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width/2, y)-(x+width/2, y+height)
   * @endcond
   */
  CENTER_TOP,

  /**
   * @cond japanese
   * @brief 中心を起点としてx, yを定義
   * 矩形は(x-width/2, y-height/2)-(x+width/2, y+height/2)
   * @endcond
   *
   * @cond english
   * @brief Defines Center-Middle coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width/2, y-height/2)-(x+width/2, y+height/2)
   * @endcond
   */
  CENTER_MIDDLE,

  /**
   * @cond japanese
   * @brief 中央下を起点としてx, yを定義
   * 矩形は(x-width/2, y-height)-(x+width/2, y)
   * @endcond
   *
   * @cond english
   * @brief Defines Center-Bottom coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width/2, y-height)-(x+width/2, y)
   * @endcond
   */
  CENTER_BOTTOM
};

}

#endif
