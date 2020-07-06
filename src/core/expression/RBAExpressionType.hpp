/**
 * Expression type enumeration class header file
 */

#ifndef RBAEXPRESSIONTYPE_HPP
#define RBAEXPRESSIONTYPE_HPP

#ifdef RBA_USE_LOG

#include <cstdint>

namespace rba
{

enum class RBAExpressionType : std::uint8_t
{
  VALUE =  0,
  BOOLEAN,
  AREA,
  CONTENT,
  SET_OF_AREA,
  SET_OF_CONTENT,
  LAMBDA,
  SCENE,
  ZONE,
  SET_OF_ZONE,
  SOUND,
  SET_OF_SOUND,
  ACTION,
  SET_OF_ACTION,
  PROPERTY,
  EXTENSION,
  CONTENT_STATE,
  EXCEPTION
};

}

#endif
#endif
