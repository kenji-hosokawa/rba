// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * View action type class
 */

#ifndef RBAVIEWACTIONTYPE_HPP
#define RBAVIEWACTIONTYPE_HPP

namespace rba
{

/**
 * @enum RBAViewActionType
 * type of view action
 */
enum class RBAViewActionType : std::uint8_t
{
  /**
   * @brief The content transition(ADD) : content is displayed in the area.
   */
  TRANSITION_ADD,

  /**
   * @brief The content transition(REMOVE) : content is deleted from the area.
   */
  TRANSITION_REMOVE,

  /**
   * @brief The content transition(REPLACE) : content is replaced on the area.
   */
  TRANSITION_REPLACE,

  /**
   * @brief The content move(MOVE) : The display of content changes to another area.
   */
  MOVE
};

}

#endif
