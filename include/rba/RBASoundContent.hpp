// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * 音声コンテントクラス
 */

#ifndef RBASOUNDCONTENT_HPP
#define RBASOUNDCONTENT_HPP

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
#include "RBAContentLoserType.hpp"

namespace rba
{

class RBASoundContentState;
class RBAZone;
  
/**
 * @cond japanese
 * @class RBASoundContent
 * 出力させる音声のオブジェクトを定義する。<br>
 * 音声コンテントは状態を複数持ち、音声コンテントがゾーンに割り当たることで、
 * アクティブな音声コンテントの状態が出力される。
 * 音声コンテントを出力可能なゾーンも、音声コンテントに定義する。
 * 出力可能なゾーンは複数定義できる。
 * @endcond
 *
 * @cond english
 * @class RBASoundContent
 * Define the object of sound content.<br>
 * Sound content has plural status.
 * When sound contents connected to a zone, active status is output.
 * Object has zone definitions, that can output itself.
 * Each object can define plural zone which can output sound contents.
 * @endcond
 */
class DLL_EXPORT RBASoundContent
{
protected:
  RBASoundContent()=default;
  RBASoundContent(const RBASoundContent&)=delete;
  RBASoundContent(RBASoundContent&&)=delete;
  RBASoundContent& operator=(const RBASoundContent&)=delete;
  RBASoundContent& operator=(RBASoundContent&&)=delete;
  ~RBASoundContent()=default;

public:
  /**
   * @cond japanese
   * @brief コンテント名を取得する
   * @return コンテント名
   * @endcond
   *
   * @cond english
   * @brief Returns the name of the sound content.
   * @return Sound content name
   * @endcond
   */
  virtual std::string getName() const=0;

  /**
   * @cond japanese
   * @brief コンテントの状態を取得する
   * @return コンテント状態のリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the state of the sound content.
   * @return List of the sound content state
   * @endcond
   */
  virtual const std::list<const RBASoundContentState*>& getContentStates() const=0;

  /**
   * @cond japanese
   * @brief 割り当てられているゾーンを取得する
   * @return ゾーンのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the zone of the sound content.
   * @return List of the zone
   * @endcond
   */
  virtual const std::list<const RBAZone*>& getZones() const=0;

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
