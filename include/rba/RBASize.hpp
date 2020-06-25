// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * Size class
 */

#ifndef RBASIZE_HPP
#define RBASIZE_HPP

#include <string>

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

namespace rba
{

/**
 * @class RBASize
 * Size definitions for object such as areas or view contents.<br>
 * Each object can define plural size.
 * Can refer to size from object.
 */
class DLL_EXPORT RBASize
{
protected:
  RBASize()=default;
  RBASize(const RBASize&)=delete;
  RBASize(RBASize&&)=delete;
  RBASize& operator=(const RBASize&)=delete;
  RBASize& operator=(RBASize&&)=delete;
  ~RBASize()=default;

public:
  /**
   * @brief Returns the name of the size.
   * @return Size name
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the width of the size.
   * @return Width of the size
   */
  virtual std::int32_t getWidth() const=0;

  /**
   * @brief Returns the height of the size.
   * @return Height of the size
   */
  virtual std::int32_t getHeight() const=0;

public:
  /**
   * @brief Default width of size
   */
  const static std::int32_t WIDTH_EDEFAULT = 0;

  /**
   * @brief Default height of size
   */
  const static std::int32_t HEIGHT_EDEFAULT = 0;

};

}

#endif
