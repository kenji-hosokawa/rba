// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * サイズクラス
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
 * @cond japanese
 * @class RBASize
 * エリアや表示コンテントの大きさを定義する。<br>
 * サイズは各エリア/表示コンテントに対して複数持つことができ、エリアや表示コンテントから
 * サイズを参照することができる。
 * @endcond
 *
 * @cond english
 * @class RBASize
 * Size definitions for object such as areas or view contents.<br>
 * Each object can define plural size.
 * Can refer to size from object.
 * @endcond
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
   * @cond japanese
   * @brief サイズ名を取得する
   * @return サイズ名
   * @endcond
   *
   * @cond english
   * @brief Returns the name of the size.
   * @return Size name
   * @endcond
   */
  virtual std::string getName() const=0;

  /**
   * @cond japanese
   * @brief サイズの幅を取得する
   * @return サイズの幅
   * @endcond
   *
   * @cond english
   * @brief Returns the width of the size.
   * @return Width of the size
   * @endcond
   */
  virtual std::int32_t getWidth() const=0;

  /**
   * @cond japanese
   * @brief サイズの高さを取得する
   * @return サイズの高さ
   * @endcond
   *
   * @cond english
   * @brief Returns the height of the size.
   * @return Height of the size
   * @endcond
   */
  virtual std::int32_t getHeight() const=0;

public:
  /**
   * @cond japanese
   * @brief デフォルトの幅
   * @endcond
   *
   * @cond english
   * @brief Default width of size
   * @endcond
   */
  const static std::int32_t WIDTH_EDEFAULT = 0;

  /**
   * @cond japanese
   * @brief デフォルトの高さ
   * @endcond
   *
   * @cond english
   * @brief Default height of size
   * @endcond
   */
  const static std::int32_t HEIGHT_EDEFAULT = 0;

};

}

#endif
