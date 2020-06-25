// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * Arbitration policy class
 */

#ifndef RBAARBITRATIONPOLICY_HPP
#define RBAARBITRATIONPOLICY_HPP

namespace rba
{

/**
 * @enum RBAArbitrationPolicy
 * Type of arbitration policy.
 */
enum class RBAArbitrationPolicy : std::uint8_t
{
  /**
   * @brief Same PRIORITY_LAST_COME_FIRST.
   */
  DEFAULT,
  /**
   * @brief First Come First Arbitration.
   * @details give priority to first come request.
   */
  FIRST_COME_FIRST,
  /**
   * @brief Last Come First Arbitration.
   * @details give priority to last come request.
   */
  LAST_COME_FIRST,
  /**
   * @brief Priority and First Come First Arbitration.
   * @details Follow the Priority of Contents.
   * If same priority then give priority to first come request.
   */
  PRIORITY_FIRST_COME_FIRST,
  /**
   * @brief Priority and Last Come First Arbitration.
   * @details Follow the Priority of Contents.
   * If same priority then give priority to last come request.
   */
  PRIORITY_LAST_COME_FIRST
};

}

#endif
