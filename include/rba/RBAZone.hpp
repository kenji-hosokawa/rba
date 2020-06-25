// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * ゾーンクラス
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
 * @cond japanese
 * @class RBAZone
 * 音声コンテントを出力させる領域を定義する。<br>
 * 1つのゾーンには高々1つの音声コンテントが割り当たって出力される。
 * 調停はゾーンごとに行われるため、調停ポリシーを定義する。
 * @endcond
 *
 * @cond english
 * @class RBAZone
 * Defines a Frame for outputting sound content.<br>
 * At run time, at most one sound content is allocated to one zone.
 * This class has arbitration policy definitions, because it is executed for each zone.
 * @endcond
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
   * @cond japanese
   * @brief ゾーン名を取得する
   * @return ゾーン名
   * @endcond
   *
   * @cond english
   * @brief Returns the name of the zone.
   * @return Zone name
   * @endcond
   */
  virtual std::string getName() const=0;

  /**
   * @cond japanese
   * @brief priorityを取得する
   * @return priority値
   * @endcond
   *
   * @cond english
   * @brief Returns the priority.
   * @return Priority value
   * @endcond
   */
  virtual std::int32_t getPriority() const=0;

  /**
   * @cond japanese
   * @brief 割り当てられているコンテントを取得する
   * @return コンテントのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the list of content which can be output in this zone.
   * @return List of content
   * @endcond
   */
  virtual const std::list<const RBASoundContent*>& getContents() const=0;

  /**
   * @cond japanese
   * @brief ゾーンに定義されている調停ポリシー値を取得する
   * @return 調停ポリシー値
   * @endcond
   *
   * @cond english
   * @brief Returns the arbitration policy value defined to this zone.
   * @return arbitration policy value
   * @endcond
   */
  virtual RBAArbitrationPolicy getArbitrationPolicy() const=0;
};

}

#endif
