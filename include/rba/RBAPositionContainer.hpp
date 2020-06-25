// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * Position container class
 */

#ifndef RBAPOSITIONCONTAINER_HPP
#define RBAPOSITIONCONTAINER_HPP

#include <cstdint>
#include "RBABasePoint.hpp"

namespace rba
{

class RBAArea;

class RBAPositionContainer
{
protected:
  RBAPositionContainer()=default;
  RBAPositionContainer(const RBAPositionContainer&)=delete;
  RBAPositionContainer(RBAPositionContainer&&)=delete;
  RBAPositionContainer& operator=(const RBAPositionContainer&)=delete;
  RBAPositionContainer& operator=(RBAPositionContainer&&)=delete;
  ~RBAPositionContainer()=default;

public:
  /**
   * @brief Get X coordinate
   * @return X coordinate
   */
  virtual std::int32_t getX() const=0;

  /**
   * @brief Get Y coordinate
   * @return Y coordinate
   */
  virtual std::int32_t getY() const=0;

  /**
   * @brief Get base point
   * @return Base point
   */
  virtual RBABasePoint getBasePoint() const=0;

  /**
   * @brief Get assigned area
   * @return assigned area
   */
  virtual const RBAArea* getArea() const=0;

public:
  /**
   * @brief default X coordinate
   */
  const static std::int32_t X_EDEFAULT=0;

  /**
   * @brief default Y coordinate
   */
  const static std::int32_t Y_EDEFAULT=0;

  /**
   * @brief default base point
   */
  const static RBABasePoint BASE_POINT_EDEFAULT=RBABasePoint::LEFT_TOP;

};

}

#endif
