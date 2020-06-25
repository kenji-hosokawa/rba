// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * エリアクラス
 */

#ifndef RBAAREA_HPP
#define RBAAREA_HPP

#include <list>
#include <string>
#include "RBAArbitrationPolicy.hpp"

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

class RBASize;
class RBAViewContent;

/**
 * @cond japanese
 * @class RBAArea
 * 画面に表示コンテントを表示させる枠を定義する。<br>
 * 1つのエリアには高々1つの表示コンテントのみ割り当たって画面に表示される。
 * @endcond
 *
 * @cond english
 * @class RBAArea
 * Defines a Frame for displaying the view content.<br>
 * At run time, at most one view content is allocated to one area.
 * @endcond
 */
class DLL_EXPORT RBAArea
{
protected:
  RBAArea()=default;
  RBAArea(const RBAArea&)=delete;
  RBAArea(RBAArea&&)=delete;
  RBAArea& operator=(const RBAArea&)=delete;
  RBAArea& operator=(RBAArea&&)=delete;
  ~RBAArea()=default;

public:
  /**
   * @cond japanese
   * @brief エリア名を取得する
   * @return エリア名
   * @endcond
   *
   * @cond english
   * @brief Returns the name of the area.
   * @return Area name
   * @endcond
   */
  virtual std::string getName() const=0;

  /**
   * @cond japanese
   * @brief エリアのベースポイントのX軸の座標値を取得する
   * @return X軸の座標値
   * @endcond
   *
   * @cond english
   * @brief Returns the x-axis value of the base point of the area
   * @return X-axis Value of the base point
   * @endcond
   */
  virtual std::int32_t getX() const=0;

  /**
   * @cond japanese
   * @brief エリアのベースポイントのY軸の座標値を取得する
   * @return Y軸の座標値
   * @endcond
   *
   * @cond english
   * @brief Returns the y-axis value of the base point of the area
   * @return Y-axis Value of the base point
   * @endcond
   */
  virtual std::int32_t getY() const=0;

  /**
   * @cond japanese
   * @brief Zオーダー値を取得する
   * Zオーダーが大きいエリアは、小さいエリアの前面に表示される。
   * @return Zオーダー値
   * @endcond
   *
   * @cond english
   * @brief Returns the z-order value.
   * An area with a large z-order value is displayed on the front of an area with small z-order value.
   * @return Z-order value
   * @endcond
   */
  virtual std::int32_t getZorder() const=0;

  /**
   * @cond japanese
   * @brief エリアに表示できる(割り当て可能な)コンテントのリストを取得する
   * @return コンテントのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the list of content which can be displayed on this area.
   * @return list of content
   * @endcond
   */
  virtual const std::list<const RBAViewContent*>& getContents() const=0;

  /**
   * @cond japanese
   * @brief エリアに定義されているサイズを取得する
   * エリアには複数のサイズを定義可能なのでリストで返す。
   * @return サイズのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the list of size defined to this area .
   * Since multiple size can be defined, returns a list of size.
   * @return list of size
   * @endcond
   */
  virtual const std::list<const RBASize*>& getSizes() const=0;

  /**
   * @cond japanese
   * @brief エリアに定義されている調停ポリシー値を取得する
   * @return 調停ポリシー値
   * @endcond
   *
   * @cond english
   * @brief Returns the arbitration policy value defined to this area.
   * @return arbitration policy value
   * @endcond
   */
  virtual RBAArbitrationPolicy getArbitrationPolicy() const=0;
};

}

#endif
