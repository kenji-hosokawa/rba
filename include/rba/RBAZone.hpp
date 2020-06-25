// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * Zone class
 */

#ifndef RBAZONE_HPP
#define RBAZONE_HPP

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

#include <list>
#include <string>
#include "RBAArbitrationPolicy.hpp"

namespace rba
{

class RBASoundContent;

/**
 * @class RBAZone
 * Defines a Frame for outputting sound content.<br>
 * At run time, at most one sound content is allocated to one zone.
 * This class has arbitration policy definitions, because it is executed for each zone.
 */
class DLL_EXPORT RBAZone
{
protected:
  RBAZone()=default;
  RBAZone(const RBAZone&)=delete;
  RBAZone(RBAZone&&)=delete;
  RBAZone& operator=(const RBAZone&)=delete;
  RBAZone& operator=(RBAZone&&)=delete;
  ~RBAZone()=default;

public:
  /**
   * @brief Returns the name of the zone.
   * @return Zone name
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the priority.
   * @return Priority value
   */
  virtual std::int32_t getPriority() const=0;

  /**
   * @brief Returns the list of content which can be output in this zone.
   * @return List of content
   */
  virtual const std::list<const RBASoundContent*>& getContents() const=0;

  /**
   * @brief Returns the arbitration policy value defined to this zone.
   * @return arbitration policy value
   */
  virtual RBAArbitrationPolicy getArbitrationPolicy() const=0;
};

}

#endif
