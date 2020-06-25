// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * モデルクラス
 */

#ifndef RBAMODEL_HPP
#define RBAMODEL_HPP

#include <string>
#include "RBAArea.hpp"
#include "RBAViewContent.hpp"
#include "RBAViewContentState.hpp"
#include "RBASize.hpp"
#include "RBAZone.hpp"
#include "RBASoundContent.hpp"
#include "RBASoundContentState.hpp"
#include "RBAScene.hpp"
#include "RBADisplay.hpp"
#include "RBAPositionContainer.hpp"
#include "RBAJsonParser.hpp"
// internal {
#include "RBAAreaSet.hpp"
#include "RBAViewContentSet.hpp"
#include "RBAZoneSet.hpp"
#include "RBASoundContentSet.hpp"
#include "RBAConstraint.hpp"
// }

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
 * @class RBAModel
 * 調停ロジックで使用する調停ルールモデルを定義する。<br>
 * エリア、ゾーン、コンテント、シーン、制約式などのモデルを構成する
 * 要素を所有する。各要素は名前による検索や、一覧を取得することができる。
 * @endcond
 *
 * @cond english
 * @class RBAModel
 * Defines the arbitration rule model which is used by Arbitrator.<br>
 * The model consists of model elements such as areas, zones, contens, scenes,
 * constraint expressions, and so on.
 * Elements can be searched by name, and the list of elements for each type can be retrieved.
 * @endcond
 */
class DLL_EXPORT RBAModel
{
public:
  RBAModel()=default;
  RBAModel(const RBAModel&)=delete;
  RBAModel(RBAModel&&)=delete;
  RBAModel& operator=(const RBAModel&)=delete;
  RBAModel& operator=(RBAModel&&)=delete;
  virtual ~RBAModel()=default;

public:
  /**
   * @cond japanese
   * @brief エリアを名前で検索する
   * @param areaName エリア名
   * @return エリア
   *
   * エリア名areaNameのエリアが存在しない場合はnullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Search for area with a name
   * @param areaName Area name
   * @return Area
   *
   * If the area name does not exist, returns nullptr.
   * @endcond
   */
  virtual const RBAArea* findArea(const std::string& areaName) const=0;

  /**
   * @cond japanese
   * @brief 表示コンテントを名前で検索する
   * @param contName コンテント名
   * @return コンテント
   *
   * コンテント名contNameの表示コンテントが存在しない場合はnullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Search for view content with a name.
   * @param contName Content name
   * @return Content
   *
   * If the content name does not exist, returns nullptr.
   * @endcond
   */
  virtual const RBAViewContent* findViewContent(const std::string& contName) const=0;

  /**
   * @cond japanese
   * @brief 表示コンテントの状態を名前で検索する
   * @param stateName コンテント状態名
   * @return 表示コンテント状態
   *
   * コンテント状態名stateNameの状態が存在しない場合はnullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Search for view content state with a name.
   * @param stateName Content state name
   * @return State of view content
   *
   * If the content state name does not exist, returns nullptr.
   * @endcond
   */
  virtual const RBAViewContentState* findViewContentState(const std::string& stateName) const=0;

  /**
   * @cond japanese
   * @brief サイズを名前で検索する
   * @param sizeName 検索するサイズの名前
   * @return サイズ
   *
   * 検索するサイズの名前は以下のように指定する。\n
   * エリアに紐づくサイズの場合：\n
   * <エリア名>/<サイズ名>\n
   * コンテントに紐づくサイズの場合：\n
   * <コンテント名>/<サイズ名>\n
   * \n
   * 検索するサイズの名前sizeNameのサイズが存在しない場合はnullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Search for size with a name.
   * @param sizeName Name of the search size
   * @return Size
   *
   * Specify the name of the search size as follows.\n
   * In the case of the size linked to the area:
   * <area_name>/<size_name>
   * In the case of the size linked to the content:
   * <content_name>/<size_name>
   * \n
   * If the name of the search size does not exist, returns nullptr.
   * @endcond
   */
  virtual const RBASize* findSize(const std::string& sizeName) const=0;

  /**
   * @cond japanese
   * @brief ゾーンを名前で検索する
   * @param zoneName ゾーン名
   * @return ゾーン
   *
   * ゾーン名zoneNameのゾーンが存在しない場合はnullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Search for zone with a name.
   * @param zoneName Zone name
   * @return Zone
   *
   * If the zone name does not exist, returns nullptr.
   * @endcond
   */
  virtual const RBAZone* findZone(const std::string& zoneName) const=0;

  /**
   * @cond japanese
   * @brief 音声コンテントを名前で検索する
   * @param contentName コンテント名
   * @return 音声コンテント
   *
   * コンテント名contentNameの音声コンテントが存在しない場合はnullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Search for sound content with a name.
   * @param contName Content name
   * @return Sound content
   *
   * If the content name does not exist, returns nullptr.
   * @endcond
   */
  virtual const RBASoundContent* findSoundContent(const std::string& contName) const=0;

  /**
   * @cond japanese
   * @brief 音声コンテントの状態を名前で検索する
   * @param stateName コンテント状態名
   * @return 音声コンテント状態
   *
   * コンテント状態名stateNameの音声コンテントが存在しない場合はnullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Search for sound content state with a name.
   * @param stateName Content state name
   * @return Sound content state
   *
   * If the content state name does not exist, returns nullptr.
   * @endcond
   */
  virtual const RBASoundContentState* findSoundContentState(const std::string& stateName) const=0;

  /**
   * @cond japanese
   * @brief シーンを名前で検索する
   * @param sceneName シーン名
   * @return シーン
   *
   * シーン名sceneNameのシーンが存在しない場合はnullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Search for scene with a name.
   * @param sceneName Scene name
   * @return Scene
   *
   * If the scene name does not exist, returns nullptr.
   * @endcond
   */
  virtual const RBAScene* findScene(const std::string& sceneName) const=0;

  /**
   * @cond japanese
   * @brief ディスプレイを名前で検索する
   * @param displayName ディスプレイ名
   * @return ディスプレイ
   *
   * ディスプレイ名displayNameのディスプレイが存在しない場合はnullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Search for display with a name.
   * @param displayName Display name.
   * @return Display
   *
   * If the display name does not exist, returns nullptr.
   * @endcond
   */
  virtual const RBADisplay* findDisplay(const std::string& displayName) const=0;

  /**
   * @cond japanese
   * @brief すべてのエリアを取得する
   * @return エリアのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the areas.
   * @return List of areas
   * @endcond
   */
  virtual const std::list<const RBAArea*>& getAreas() const=0;

  /**
   * @cond japanese
   * @brief すべての表示コンテントを取得する
   * @return 表示コンテントのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the view contents.
   * @return List of contents
   * @endcond
   */
  virtual const std::list<const RBAViewContent*>& getViewContents() const=0;

  /**
   * @cond japanese
   * @brief すべての表示コンテント状態を取得する
   * @return 表示コンテント状態のリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the view content states.
   * @return List of view content states
   * @endcond
   */
  virtual const std::list<const RBAViewContentState*>& getViewContentStates() const=0;

  /**
   * @cond japanese
   * @brief すべてのサイズを取得する
   * @return サイズのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the sizes.
   * @return List of sizes
   * @endcond
   */
  virtual const std::list<const RBASize*>& getSizes() const=0;

  /**
   * @cond japanese
   * @brief すべてのゾーンを取得する
   * @return ゾーンのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the zones.
   * @return List of zones
   * @endcond
   */
  virtual const std::list<const RBAZone*>& getZones() const=0;

  /**
   * @cond japanese
   * @brief すべての音声コンテントを取得する
   * @return 音声コンテントのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the sound contents.
   * @return List of sound contents
   * @endcond
   */
  virtual const std::list<const RBASoundContent*>& getSoundContents() const=0;

  /**
   * @cond japanese
   * @brief すべての音声コンテント状態を取得する
   * @return 音声コンテント状態のリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the sound content states.
   * @return List of sound content states
   * @endcond
   */
  virtual const std::list<const RBASoundContentState*>& getSoundContentStates() const=0;

  /**
   * @cond japanese
   * @brief すべてのシーンを取得する
   * @return シーンのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the scenes.
   * @return List of scenes
   * @endcond
   */
  virtual const std::list<const RBAScene*>& getScenes() const=0;

  /**
   * @cond japanese
   * @brief すべてのディスプレイを取得する
   * @return ディスプレイのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the displays.
   * @return List of displays
   * @endcond
   */
  virtual const std::list<const RBADisplay*>& getDisplays() const=0;

  // internal {
  /**
   * @cond japanese
   * @brief モデル要素を名前で検索する
   * @param elementName モデル要素名
   * @return モデル要素
   *
   * モデル要素名elementNameのモデル要素が存在しない場合はnullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Search for Model element with a name.
   * @param elementName Model element name.
   * @return Model element
   *
   * If the Model element name does not exist, returns nullptr.
   * @endcond
   */
  virtual const RBAModelElement* findModelElement(const std::string& elementName) const=0;

  /**
   * @cond japanese
   * @brief すべてのエリアセットを取得する
   * @return エリアセットのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the sets of areas.
   * @return List of sets of areas
   * @endcond
   */
  virtual const std::list<const RBAAreaSet*>& getAreaSets() const=0;

  /**
   * @cond japanese
   * @brief すべての表示コンテントセットを取得する
   * @return 表示コンテントセットのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the sets of view contents.
   * @return List of sets of view contents
   * @endcond
   */
  virtual const std::list<const RBAViewContentSet*>& getViewContentSets() const=0;

  /**
   * @cond japanese
   * @brief すべてのポジションコンテナを取得する
   * @return ポジションコンテナのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the position containers.
   * @return List of sets of position containers
   * @endcond
   */
  virtual const std::list<const RBAPositionContainer*>& getPositionContainers() const=0;

  /**
   * @cond japanese
   * @brief すべての制約式を取得する
   * @return 制約式のリスト
   * @endcond
   *
   * @cond english
   * @brief Returns all the constraints.
   * @return List of constraints
   * @endcond
   */
  virtual std::list<RBAConstraint*>& getConstraints()=0;

 // }

};

}

#endif
