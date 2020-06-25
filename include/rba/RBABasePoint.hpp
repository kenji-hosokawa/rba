// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * Base point class
 */

#ifndef RBABASEPOINT_HPP
#define RBABASEPOINT_HPP

namespace rba
{

/**
 * @enum RBABasePoint
 * Base point for object having size. For example Area.
 */
enum class RBABasePoint : std::uint8_t
{
  /**
   * @brief Defines Left-Top coordinate as the base point of (x, y)
   * The rectangle is represented by (x, y)-(x+width, y+height)
   */
  LEFT_TOP,

  /**
   * @brief Defines Left-Middle coordinate as the base point of (x, y)
   * The rectangle is represented by (x, y-height/2)-(x+width, y+height/2)
   */
  LEFT_MIDDLE,

  /**
   * @brief Defines Left-Bottom coordinate as the base point of (x, y)
   * The rectangle is represented by (x, y-height)-(x+width, y)
   */
  LEFT_BOTTOM,

  /**
   * @brief Defines Right-Top coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width, y)-(x, y+height)
   */
  RIGHT_TOP,

  /**
   * @brief Defines Right-Middle coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width, y-height/2)-(x, y+height/2)
   */
  RIGHT_MIDDLE,

  /**
   * @brief Defines Right-Bottom coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width, y-height)-(x, y)
   */
  RIGHT_BOTTOM,

  /**
   * @brief Defines Center-Top coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width/2, y)-(x+width/2, y+height)
   */
  CENTER_TOP,

  /**
   * @brief Defines Center-Middle coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width/2, y-height/2)-(x+width/2, y+height/2)
   */
  CENTER_MIDDLE,

  /**
   * @brief Defines Center-Bottom coordinate as the base point of (x, y)
   * The rectangle is represented by (x-width/2, y-height)-(x+width/2, y)
   */
  CENTER_BOTTOM
};

}

#endif
