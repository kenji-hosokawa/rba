// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * Result status type cluss
 */

#ifndef RBARESULTSTATUSTYPE_HPP
#define RBARESULTSTATUSTYPE_HPP

namespace rba
{

/**
 * @enum RBAResultStatusType
 * Status of the arbitration result.
 */
enum class RBAResultStatusType : std::uint8_t
{
  /**
   * @brief Success
   */
  SUCCESS,

  /**
   * @brief Failed
   */
  FAILED,

  /**
   * @brief Unknown context or content state
   */
  UNKNOWN_CONTENT_STATE,

  /**
   * @brief Cancel arbitration error
   */
  CANCEL_ERROR

};

}

#endif
