// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * ビューアクションタイプクラス
 */

#ifndef RBAVIEWACTIONTYPE_HPP
#define RBAVIEWACTIONTYPE_HPP

namespace rba
{

/**
 * @cond japanese
 * @enum RBAViewActionType
 * 表示アクションの種類を示す
 * @endcond
 *
 * @cond english
 * @enum RBAViewActionType
 * type of view action
 * @endcond
 */
enum class RBAViewActionType : std::uint8_t
{
  /**
   * @cond japanese
   * @brief コンテント遷移(ADD)：コンテントがエリアに表示された
   * @endcond
   *
   * @cond english
   * @brief The content transition(ADD) : content is displayed in the area.
   * @endcond
   */
  TRANSITION_ADD,

  /**
   * @cond japanese
   * @brief コンテント遷移(REMOVE)：コンテントがエリアから消去された
   * @endcond
   *
   * @cond english
   * @brief The content transition(REMOVE) : content is deleted from the area.
   * @endcond
   */
  TRANSITION_REMOVE,

  /**
   * @cond japanese
   * @brief コンテント遷移(REPLACE)：エリアのコンテントが置き換えられた
   * @endcond
   *
   * @cond english
   * @brief The content transition(REPLACE) : content is replaced on the area.
   * @endcond
   */
  TRANSITION_REPLACE,

  /**
   * @cond japanese
   * @brief コンテント移動(MOVE)：コンテントが表示されているエリアが変わった
   * @endcond
   *
   * @cond english
   * @brief The content move(MOVE) : The display of content changes to another area.
   * @endcond
   */
  MOVE
};

}

#endif
