// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * ディスプレイクラス
 */

#ifndef RBADISPLAY_HPP
#define RBADISPLAY_HPP

#include <list>
#include <string>

namespace rba {

class RBAArea;
class RBASize;

/**
 * @cond japanese
 * @class RBADisplay
 * 1つの画面構成（ディスプレイ）を定義する。<br>
 * 複数定義した場合、マルチ画面構成となる。
 * ディスプレイでは、ディスプレイに配置されるエリアの集合を定義する。
 * @endcond
 *
 * @cond english
 * @class RBADisplay
 * Defines a screen layout of the display.<br>
 * You can define multiple displays for Multi-Display products.
 * Display defines a set of areas which are laid out on it.
 * @endcond
 */
class RBADisplay
{
protected:
  RBADisplay()=default;
  RBADisplay(const RBADisplay&)=delete;
  RBADisplay(RBADisplay&&)=delete;
  RBADisplay& operator=(const RBADisplay&)=delete;
  RBADisplay& operator=(RBADisplay&&)=delete;
  ~RBADisplay()=default;

public:
  /**
   * @cond japanese
   * @brief ディスプレイ名を取得する
   * @return ディスプレイ名
   * @endcond
   *
   * @cond english
   * @brief Returns the name of display
   * @return Display name
   * @endcond
   */
  virtual std::string getName() const=0;

  /**
   * @cond japanese
   * @brief ディスプレイに割り当てられているサイズを取得する
   * @return サイズ
   * @endcond
   *
   * @cond english
   * @brief Returns the size of display
   * @return Size
   * @endcond
   */
  virtual const RBASize* getSize() const=0;

  /**
   * @cond japanese
   * @brief ディスプレイに割り当てられているエリアを取得する
   * @return エリアのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns areas which are allocated to the display
   * @return List of area
   * @endcond
   */
  virtual const std::list<const RBAArea*>& getAreas() const=0;

};

}

#endif
