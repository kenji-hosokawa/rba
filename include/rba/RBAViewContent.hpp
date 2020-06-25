// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * 表示コンテントクラス
 */

#ifndef RBAVIEWCONTENT_HPP
#define RBAVIEWCONTENT_HPP

#include <list>
#include <string>
#include "RBAContentLoserType.hpp"

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

class RBAViewContentState;
class RBAArea;
class RBASize;
  
/**
 * @cond japanese
 * @class RBAViewContent
 * エリアに表示させるオブジェクトを定義する。<br>
 * 表示コンテントは状態を複数持ち、表示コンテントがエリアに割り当たることで、
 * アクティブな表示コンテント状態が表示される。
 * 表示コンテントは表示可能なエリアを複数定義することができる。
 * @endcond
 *
 * @cond english
 * @class RBAViewContent
 * Define the object of view content.<br>
 * View content has plural status.
 * When view contents connected to a area, active status is displayed.
 * Each object can define plural area which can displayed view contents.
 * @endcond
 */
class DLL_EXPORT RBAViewContent
{
protected:
  RBAViewContent()=default;
  RBAViewContent(const RBAViewContent&)=delete;
  RBAViewContent(RBAViewContent&&)=delete;
  RBAViewContent& operator=(const RBAViewContent&)=delete;
  RBAViewContent& operator=(RBAViewContent&&)=delete;
  ~RBAViewContent()=default;

public:
  /**
   * @cond japanese
   * @brief コンテント名を取得する
   * @return コンテント名
   * @endcond
   *
   * @cond english
   * @brief Returns the name of the view content.
   * @return View content name
   * @endcond
   */
  virtual std::string getName() const=0;

  /**
   * @cond japanese
   * @brief コンテントの状態を取得する
   * @return コンテントの状態のリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the state of the view content.
   * @return List of view content state
   * @endcond
   */
  virtual const std::list<const RBAViewContentState*>& getContentStates() const=0;

  /**
   * @cond japanese
   * @brief 割り当てられているエリアを取得する
   * @return エリアのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the area of the view content.
   * @return List of the area
   * @endcond
   */
  virtual const std::list<const RBAArea*>& getAreas() const=0;

  /**
   * @cond japanese
   * @brief 割り当てられているサイズを取得する
   * @return サイズのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the list of size assignment to this content.
   * @return List of size
   * @endcond
   */
  virtual const std::list<const RBASize*>& getSizes() const=0;

  /**
   * @cond japanese
   * @brief ルーザータイプを取得する
   * @return ルーザータイプ
   * @endcond
   *
   * @cond english
   * @brief Returns the loser type.
   * @return Loser type
   * @endcond
   */
  virtual RBAContentLoserType getLoserType() const=0;

public:
  /**
   * @cond japanese
   * @brief デフォルトのルーザータイプ
   * @endcond
   *
   * @cond english
   * @brief Defines the default loser type.
   * @endcond
   */
  const static RBAContentLoserType LOSER_TYPE_EDEFAULT =
    RBAContentLoserType::NEVER_GIVEUP;

};

}

#endif
