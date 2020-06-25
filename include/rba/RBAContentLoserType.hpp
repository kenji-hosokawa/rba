// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * Good loser type class
 */

#ifndef RBACONTENTLOSERTYPE_HPP
#define RBACONTENTLOSERTYPE_HPP

namespace rba
{

/**
 * @enum RBAContentLoserType
 * Type of behavior when content loses the arbitration
 */
enum class RBAContentLoserType : std::uint8_t
{
  /**
   * @brief Always cancels its request when losing arbitration.
   */
  GOOD_LOSER=0,

  /**
   * @brief Cancels its request only if it lost the arbitration in the displaying state.
   */
  DO_NOT_GIVEUP_UNTIL_WIN,

  /**
   * @brief Never cancels its request.
   */
  NEVER_GIVEUP
};

}

#endif
