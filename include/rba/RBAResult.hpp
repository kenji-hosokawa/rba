// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * @cond japanese
 * 調停結果クラス
 * @endcond
 *
 * @cond english
 * Arbitration result class
 * @endcond
 */

#ifndef RBARESULT_HPP
#define RBARESULT_HPP

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

#include <memory>
#include <list>
#include "RBAResultStatusType.hpp"
#include "RBAViewAction.hpp"
#include "RBAScene.hpp"

namespace rba
{

class RBAArea;
class RBAViewContent;
class RBAViewContentState;
class RBAScene;
class RBASize;
class RBAZone;
class RBASoundContent;
class RBASoundContentState;
// internal {
class RBADisplay;
// }

/**
 * @cond japanese
 * @class RBAResult
 * 調停結果を保持するクラス。\n
 * 調停によりエリアにコンテントが割り当てられ、それらの関連情報を取得することができる。\n
 * 調停結果は、各エリア/ゾーンにどのコンテントが割り当たったかを示す。
 * また、スナップショット情報と、前回の調停結果からの差分を示すビューアクション情報(表示の結果
 * のみ)が含まれる。
 * @endcond
 *
 * @cond english
 * @class RBAResult
 * Stores an arbitration result.<br>
 * The Arbitrator allocates Contents to Areas. Related
 * information of those can be acquired from RBAResult.\n
 * The arbitration result indicates which content is allocated to each 
 * area / zone.
 * Also, snapshot information and view action information (only display
 * results) indicating the difference from the last arbitration are included.
 * @endcond
 */
class DLL_EXPORT RBAResult
{
public:
  RBAResult()=default;
  RBAResult(const RBAResult&)=delete;
  RBAResult(RBAResult&&)=delete;
  RBAResult& operator=(const RBAResult&)=delete;
  RBAResult& operator=(RBAResult&&)=delete;
  virtual ~RBAResult()=default;

public:

  // [VisibleArea/SoundingZone]

  /**
   * @cond japanese
   * @brief 表示状態のエリアを取得する
   * @return 表示エリアのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the displaying areas determined by the last arbitration.
   * @return List of visible areas.
   * @endcond
   */
  virtual const std::list<const RBAArea*>& getVisibleAreas() const=0;

  /**
   * @cond japanese
   * @brief 出力状態のゾーンを取得する
   * @return 出力ゾーンのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the outputting zones determined by the last arbitration.
   * @return List of sounding zones.
   * @endcond
   */
  virtual const std::list<const RBAZone*>& getSoundingZones() const=0;

  // [Visible/Sounding ContentStates]

  /**
   * @cond japanese
   * @brief 表示状態の表示コンテントステートを取得する
   * @return 表示状態の表示コンテントステートのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the view content states to be displayed determined by the last arbitration.
   * @return List of visible view content states.
   * @endcond
   */
  virtual const std::list<const RBAViewContentState*>& getVisibleContentStates() const=0;

  /**
   * @cond japanese
   * @brief 出力状態の音声コンテントステートを取得する
   * @return 出力状態の音声コンテントステートのリスト
   * @details 減衰出力状態の音声コンテントステートも取得される
   * @endcond
   *
   * @cond english
   * @brief Returns the sound content states to be output determined by the last arbitration.
   * @return List of sound content states to be output.
   * @details The list contains sound contents to be attenuated.
   * @endcond
   */
  virtual const std::list<const RBASoundContentState*>& getSoundingContentStates() const=0;

  // [Active View/Sound ContentStates]

  /**
   * @cond japanese
   * @brief 表示要求状態の表示コンテントステートを取得する
   * @return 表示要求状態の表示コンテントステートのリスト
   * @details
   * 表示要求状態の表示コンテントステートは、これまでに表示要求のあった表示コンテントステートの累積であり、
   * 表示取り下げ要求や、負け時アクションにより表示要求がキャンセルされたコンテントステートは含まない。
   * @endcond
   *
   * @cond english
   * @brief Returns the active view content states at the last arbitration
   * result.
   * @return List of active view content states.
   * @details
   * The active view content states are those that have been requested to
   * display so far.　They do not include the view content state whose request
   * has been withdrawn or canceled.
   *
   * @endcond
   */
  virtual const std::list<const RBAViewContentState*>& getActiveViewContentStates() const=0;

  /**
   * @cond japanese
   * @brief 出力要求状態の音声コンテントステートを取得する
   * @return 出力要求状態の音声コンテントステートのリスト
   * @details
   * 出力要求状態の音声コンテントステートは、これまでに出力要求のあった音声コンテントステートの累積であり、
   * 出力取り下げ要求や、負け時アクションにより出力要求がキャンセルされたコンテントステートは含まない。
   * @endcond
   *
   * @cond english
   * @brief Returns the active sound content states at the last arbitration
   * result.
   * @return List of active sound content states.
   * @details
   * The active sound content states are those that have been requested to
   * output so far.　They do not include the sound content state whose request
   * has been withdrawn or canceled.
   *
   * @endcond
   */
  virtual const std::list<const RBASoundContentState*>& getActiveSoundContentStates() const=0;

  // [Active Scenes]

  /**
   * @cond japanese
   * @brief ON状態のシーンを取得する
   * @return ON状態のシーンのリスト
   * @details
   * ON状態のシーンは、これまでにシーンONを通知されたシーンや、制御実行式でON状態となったシーンの累積であり、
   * その後OFF要求のあったシーンや制御実行式でOFF状態となったシーンは含まない。
   * @endcond
   *
   * @cond english
   * @brief Returns the active scenes at the last arbitration.
   * @return List of active scenes.
   * @details
   * The active scenes are those that have been requested for ON so far.
   * They do not include scenes requested for OFF afterwards.
   *
   * @endcond
   */
  virtual const std::list<const RBAScene*>& getActiveScenes() const=0;

  // [InvisibleAreas/UnsoundingZone]

  /**
   * @cond japanese
   * @brief 非表示エリアを取得する
   * @return 非表示エリアのリスト
   * @details
   * すべてのエリアのうち表示されていないエリアを返す。\n
   * 隠蔽されているエリアも取得される。
   * @endcond
   *
   * @cond english
   * @brief Returns the invisible areas determined by the last arbitration.
   * @return List of invisible areas.
   * @details
   * Returns the areas which are not displayed out of all areas.\n
   * The list contains areas to be hidden.
   * @endcond
   */
  virtual const std::list<const RBAArea*>& getInvisibleAreas() const=0;

  /*
   * @cond japanese
   * @brief 非出力ゾーンを取得する
   * @return 非出力ゾーンのリスト
   * @details
   * すべてのゾーンのうち出力されていないゾーンを返す。\n
   * ミュートされているゾーンも取得される。
   * @endcond
   *
   * @cond english
   * @brief Returns the unsounding zones determined by the last arbitration.
   * @return List of unsounding zones.
   * @details
   * Returns the zones which are not output out of all zones.
   * The list contains zones to be muted.
   * @endcond
   */
  virtual const std::list<const RBAZone*>& getUnsoundingZones() const=0;

  // [HiddenAreas/MuteZones]

  /**
   * @cond japanese
   * @brief 隠蔽状態のエリアを取得する
   * @return 隠蔽状態のエリアのリスト
   * @details
   * すべてのエリアのうち、隠蔽状態でかつコンテントが割り当てられたエリアを返す。\n
   * 隠蔽状態とは、制約式によってそのエリアが隠蔽状態でなければならない、と制約されている
   * 状態を指す。
   * @endcond
   *
   * @cond english
   * @brief Returns the area that is hidden state and content has been
   * allocated.\n
   * The hidden state is a state in which the area must be hidden by a
   * constraint expression.
   * @return List of areas.
   * Returns the area which become to be invisible.
   * The area invisible in the previous time is not included.
   * @endcond
   */
  virtual const std::list<const RBAArea*>& getHiddenAreas() const=0;

  /**
   * @cond japanese
   * @brief ミュート状態のゾーンを取得する
   * @return ミュート状態のゾーンのリスト
   * @details
   * すべてのゾーンのうち、ミュート状態でかつコンテントが割り当てられたゾーンを返す。\n
   * ミュート状態とは、制約式によってそのゾーンがミュート状態でなければならない、
   * と制約されている状態を指す。
   * @endcond
   *
   * @cond english
   * @brief Returns the zone that is muted state and content has been
   * allocated.\n
   * The muted state is a state in which the zone must be muted by a
   * constraint expression.
   * @return List of muted zones.
   *
   * Retuens the zones that is defeted and canceled sound contents.
   * @endcond
   */
  virtual const std::list<const RBAZone*>& getMuteZones() const=0;

  // [get Attenuated]

  /**
   * @cond japanese
   * @brief 減衰出力状態のゾーンを取得する
   * @return 減衰出力状態のゾーンのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the attenuated zones determined by the last arbitration.
   * @return List of attenuated zones.
   * @endcond
   */
  virtual const std::list<const RBAZone*>& getAttenuatedZones() const=0;

  // [Canceled Contents]

  /**
   * @cond japanese
   * @brief 今回の調停処理で、調停負けにより表示要求がキャンセルされた表示コンテントを取得する
   * @return 今回の調停処理で、調停負けにより表示要求がキャンセルされた表示コンテントのリスト
   * @details
   * 今回の調停処理で、負け時アクションで要求キャンセルされた表示コンテントを取得する。\n
   * 表示取り下げ要求により、表示要求が取り下げられたものは取得しない。
   * @endcond
   *
   * @cond english
   * @brief Returns the canceled view contents determined by the last arbitration.
   * @return List of canceled view contents.
   * @details
   * Reterns list of view contents which are canceled by Request handling on lost definition\n
   * such as Loser Type and Post Constraints.\n
   * The list does not contain contents which are withdrawn.
   * @endcond
   */
  virtual const std::list<const RBAViewContent*>& getCanceledViewContents() const=0;

  /**
   * @cond japanese
   * @brief 今回の調停処理で、調停負けにより出力要求がキャンセルされた音声コンテントを取得する
   * @return 今回の調停処理で、調停負けにより出力要求がキャンセルされた音声コンテントのリスト
   * @details
   * 今回の調停処理で、負け時アクションで要求キャンセルされた音声コンテントを取得する。\n
   * 出力取り下げ要求により、出力要求が取り下げられたものは取得しない。
   * @endcond
   *
   * @cond english
   * @brief Returns the canceled sound contents determined by the last arbitration.
   * @return List of canceled sound contents.
   * @details
   * Reterns list of sound contents which are canceled by Request handling on lost definition\n
   * such as Loser Type and Post Constraints.\n
   * The list does not contain contents which are withdrawn.
   * @endcond
   */
  virtual const std::list<const RBASoundContent*>& getCanceledSoundContents() const=0;

  // [Standby Contents]

  /**
   * @cond japanese
   * @brief 調停負けにより待機状態となっている表示コンテントを取得する
   * @return 調停負けにより待機状態となっている表示コンテントのリスト
   * @details
   * 表示要求があり、エリアに割り当たっていない表示コンテントを取得する。
   * 負け時アクションにより、要求がキャンセルされた表示コンテントや、
   * エリアに割り当たっているが、エリアが隠蔽されている表示コンテントは取得しない。
   * @endcond
   *
   * @cond english
   * @brief Returns the stand by view contents due to defeated at the last
   * arbitration.
   * @return List of stand by view contents.
   * @details
   * Returns list of view contents which are active but not allocated to any area.
   * The list does not contains which are canceled contents or are allocated to hidden area.
   * @endcond
   */
  virtual const std::list<const RBAViewContent*>& getStandbyViewContents() const=0;

  /**
   * @cond japanese
   * @brief 調停負けにより待機状態となっている音声コンテントを取得する
   * @return 調停負けにより待機状態となっている音声コンテントのリスト
   * @details
   * 出力要求があり、ゾーンに割り当たっていない音声コンテントを取得する。
   * 負け時アクションにより、要求がキャンセルされた音声コンテントや、
   * ゾーンに割り当たっているが、ゾーンがミュートされている音声コンテントは取得しない。
   * @endcond
   *
   * @cond english
   * @brief Returns the stand by sound contents due to defeated at the last
   * arbitration.
   * @return List of stand by sound contents.
   * @details
   * Returns list of sound contents which are active but not allocated to any area.
   * The list does not contains which are canceled contents or are allocated to muted area.
   * @endcond
   */
  virtual const std::list<const RBASoundContent*>& getStandbySoundContents() const=0;

  // [ContentStates]

  /**
   * @cond japanese
   * @brief エリアに割り当てられている表示コンテントステートを取得する
   * @param area エリア
   * @return areaに割り当てられている表示コンテントステート
   * @details
   * areaに表示コンテントステートが割り当てられていなかった場合は、nullptrを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないareaを指定された場合は、nullptrを返す。\n
   * areaにnullptrを指定された場合は、nullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the view content state assigned to the area of the last
   * arbitration.
   * @param area Area
   * @return The view content state assign to the area.
   * @details
   * If no view content state is allocated to the area, nullptr is returnd.\n
   * If area is not defined in the Model or nullptr, nullptr is returnd.
   * @endcond
   */
  virtual const RBAViewContentState* getContentState(const RBAArea* area) const=0;

  /**
   * @cond japanese
   * @brief ゾーンに割り当てられている音声コンテントステートを取得する
   * @param zone ゾーン
   * @return zoneに割り当てられている音声コンテントステート
   * @details
   * zoneに音声コンテントステートが割り当てられていなかった場合は、nullptrを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないzoneを指定された場合は、nullptrを返す。\n
   * zoneにnullptrを指定された場合は、nullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the sound content state assigned to the zone of the last
   * arbitration.
   * @param zone Zone
   * @return The sound content state assign to the zone.
   * @details
   * If no sound content state is allocated to the zone, nullptr is returned.\n
   * If zone is not defined in the Model or nullptr, nullptr is returnd.
   * @endcond
   */
  virtual const RBASoundContentState* getContentState(const RBAZone* zone) const=0;

  // [Areas/Zones by ConentState]

  /**
   * @cond japanese
   * @brief 表示コンテントステートを割り当てているエリアを取得する
   * @param state 表示コンテントステート
   * @return 表示コンテントステートを割り当てているエリアのリスト
   * @details
   * 表示コンテントステートがエリアに割り当てられていなかった場合は、空のリストを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、空のリストを返す。\n
   * stateにnullptrを指定された場合は、空のリストを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the area to which the view content state is allocated at the
   * last arbitration.
   * @param state View content state
   * @return The areas to which the view content state.
   * @details
   * If the view content state is not assigned to any area, empty list is returned.\n
   * If state is not defined in the Model or nullptr, empty list is returned.
   * @endcond
   */
  virtual const std::list<const RBAArea*> getArea(const RBAViewContentState* state) const=0;

  /**
   * @cond japanese
   * @brief 音声コンテントステートを割り当てているゾーンを取得する
   * @param state 音声コンテントステート
   * @return 音声コンテントステートを割り当てているゾーンのリスト
   * @details
   * 音声コンテントステートがゾーンに割り当てられていなかった場合は、空のリストを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、空のリストを返す。\n
   * stateにnullptrを指定された場合は、空のリストを返す。
   * @endcond
   *
   * @cond english
   * @brief Get the zone to which the sound content state is allocated of the
   * last arbitration.
   * @param state Sound content state
   * @return The zones to which the sound content state is allocated.
   * @details
   * If the sound content state is not assigned to any zone,
   * empty list is retuened.\n
   * If state is not defined in the Model or nullptr, empty list is returned.
   * @endcond
   */
  virtual const std::list<const RBAZone*> getZone(const RBASoundContentState* state) const=0;

  // [Areas/Zones by Content]

  /**
   * @cond japanese
   * @brief 表示コンテントを割り当てているエリアを取得する
   * @param content 表示コンテント
   * @return 表示コンテントを割り当てているエリアのリスト
   * @details
   * 表示コンテントがエリアに割り当てられていなかった場合は、空のリストを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないcontentを指定された場合は、空のリストを返す。\n
   * contentにnullptrを指定された場合は、空のリストを返す。\n
   * getArea(RBAViewContentState*)との違いは引数の型のみであり、
   * 同じコンテントに対する要求であれば、戻り値は必ず一致する。
   * @endcond
   *
   * @cond english
   * @brief Returns the area to which the view content is allocated of the
   * last arbitration.
   * @param content View content
   * @return The areas to which the view content is allocated.
   * @details
   * If the view content is not assigned to any area, empty list is returned.\n
   * If content is not defined in the Model or nullptr, empty list is returned.\n
   * This API is the same as getArea(RBAViewContentState*) \n
   * except for the type of argument.
   * @endcond
   */
  virtual const std::list<const RBAArea*> getArea(const RBAViewContent* content)const=0;

  /**
   * @cond japanese
   * @brief 音声コンテントを割り当てているゾーンを取得する
   * @param content 音声コンテント
   * @return 音声コンテントを割り当てているゾーンのリスト
   * @details
   * 音声コンテントがゾーンに割り当てられていなかった場合は、空のリストを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないcontentを指定された場合は、空のリストを返す。\n
   * contentにnullptrを指定された場合は、空のリストを返す。\n
   * getZone(RBASoundContentState*)との違いは引数の型のみであり、
   * 同じコンテントに対する要求であれば、戻り値は必ず一致する。
   * @endcond
   *
   * @cond english
   * @brief Returns the zone to which the sound content state is allocated of the
   * last arbitration.
   * @param content Sound content
   * @return The zones to which the sound content is allocated.
   * @details
   * If the sound content is not assigned to any area, nullptr is returned.\n
   * If content is not defined in the Model or nullptr, empty list is returned.\n
   * This API is the same as getZone(RBASoundContentState*) \n
   * except for the type of argument.
   * @endcond
   */
  virtual const std::list<const RBAZone*> getZone(const RBASoundContent* content) const=0;

  // [Size]

  /**
   * @cond japanese
   * @brief 今回調停結果での、エリアのサイズを取得する
   * @param area エリア
   * @return エリアのサイズ
   * @details
   * エリアには複数のサイズを定義することができ、そのサイズは表示コンテントに合わせて変化する。\n
   * エリアに割り当たっている表示コンテントに合わせたサイズを応答する。\n
   * エリアに表示コンテントが割り当てられていなかった場合は、nullptrを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないエリアを指定された場合は、nullptrを返す。\n
   * areaにnullptrを指定された場合は、nullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the size of the area determined in the last arbitration.
   * @param area Area
   * @return The size of the area.
   * @details
   * Area may have multiple sizes and its size will vary by the allocated content.\n
   * This API returns the size which are matched with allocated content.\n
   * If no content is allocated to the area, returns nullptr.\n
   * If area is not defined in the Model or nullptr, returns nullptr.
   * @endcond
   */
  virtual const RBASize* getSize(const RBAArea* area) const=0;

  // [Active check Scene]

  /**
   * @cond japanese
   * @brief シーンがON状態かチェックする
   * @param scene ON状態かチェックするシーン
   * @return true:ON状態\n
   * false:OFF状態
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がないシーンを指定された場合は、falseを返す。\n
   * sceneにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the scene is ON at the last arbitration.
   * @param scene Reference scene to be checked.
   * @return true: the scene is ON
   * @return false: the scene is OFF
   * @details
   * If scene is not defined in the Model or nullptr, returns false.
   *
   * @endcond
   */
  virtual bool isActive(const RBAScene* scene) const=0;

  // [Active check ContentState]

  /**
   * @cond japanese
   * @brief 表示コンテントが表示要求状態かチェックする
   * @param content 表示要求状態かチェックする表示コンテント
   * @return true:表示要求状態である
   * @return false:表示要求状態でない
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がない表示コンテントを指定された場合は、falseを返す。\n
   * contentにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the view content is active.
   * @param state Reference view content to be checked.
   * @return true: Active
   * @return false: Not active
   * @details
   * If content is not defined in the Model or nullptr, returns false.
   * @endcond
   */
  virtual bool isActive(const RBAViewContent* content) const=0;

  /**
   * @cond japanese
   * @brief 音声コンテントが出力要求状態かチェックする
   * @param content 表示要求状態かチェックする出力コンテント
   * @return true:出力要求状態である
   * @return false:出力要求状態でない
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がない音声コンテントを指定された場合は、falseを返す。\n
   * contentにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the sound content is active.
   * @param state Reference sound content to be checked.
   * @return true: Active
   * @return false: Not active
   * @details
   * If content is not defined in the Model or nullptr, returns false.
   * @endcond
   */
  virtual bool isActive(const RBASoundContent* content) const=0;

  // [Visible/Sounding Area/Zonecheck]

  /**
   * @cond japanese
   * @brief エリアが表示状態であるかチェックする
   * @param area チェックするエリア
   * @return true:表示状態である
   * @return false:非表示状態である
   * @details
   * 隠蔽されているエリアはfalseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないareaを指定された場合は、falseを返す。\n
   * areaにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the area is visible of the last arbitration.
   * @param area Reference area to be checked.
   * @return true: Visible
   * @return false: Not visible
   * @details
   * Returns false if the area is hidden.\n
   * If area is not defined in the Model or nullptr, returns false.
   * @endcond
   */
  virtual bool isVisible(const RBAArea* area) const=0;

  /**
   * @cond japanese
   * @brief ゾーンが出力状態であるかチェックする
   * @param zone チェックするゾーン
   * @return true:出力状態である
   * @return false:非出力状態である
   * @details
   * ミュートされているエリアはfalseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないzoneを指定された場合は、falseを返す。\n
   * zoneにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the zone is sounding of the last arbitration.
   * @param zone Reference zone to be checked.
   * @return true: Sounding
   * @return false: Not sounding
   * @details
   * Returns false if the zone is muted.\n
   * If zone is not defined in the Model or nullptr, returns false.
   * @endcond
   */
  virtual bool isSounding(const RBAZone* zone) const=0;

  // [Visible/Sounding ContentState check]

  /**
   * @cond japanese
   * @brief 表示コンテントステートが表示状態であるかチェックする
   * @param state チェックする表示コンテントステート
   * @return true:stateが表示エリアに割り当てられている
   * @return false:stateが表示エリアに割り当てられていない
   * @details
   * 隠蔽されているエリアにのみ割り当てられている場合はfalseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、falseを返す。\n
   * stateにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the view content state is visible
   * of the last arbitration.
   * @param state Reference view content state to be checked.
   * @return true: state is allocated to visible area.
   * @return false: state is not allocated to visible area.
   * @details
   * If all of the areas to which the content is allocated are hidden, returns false\n
   * If state is not defined in the Model or nullptr, returns false.
   * @endcond
   */
  virtual bool isVisible(const RBAViewContentState* state) const=0;

  /**
   * @cond japanese
   * @brief 音声コンテントステートが出力状態であるかチェックする
   * @param state チェックする音声コンテントステート
   * @return true:stateが出力ゾーンに割り当てられている
   * @return false:stateが出力ゾーンに割り当てられていない
   * @details
   * ミュートされているゾーンにのみ割り当てられている場合はfalseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、falseを返す。\n
   * stateにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the sound content state is sounding
   * of the last arbitration.
   * @param state Reference sound content state to be check.
   * @return true: state is allocated to outputting zone.
   * @return false: state is not allocated to outputting zone.
   * @details
   * If all of the zones to which the content is allocated are muted, returns false\n
   * If state is not defined in the Model or nullptr, returns false.
   * @endcond
   */
  virtual bool isSounding(const RBASoundContentState* state) const=0;

  // [View/Sound ContentState]

  /**
   * @cond japanese
   * @brief エリアに割り当たっている表示コンテントステートを取得する
   * @param area エリア
   * @return エリアに割り当たっている表示コンテントステート
   * @details
   * エリアが隠蔽されている場合も、割り当たっている表示コンテントステートを返す。\n
   * areaに表示コンテントステートが割り当てられていない場合は、nullptrを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないareaを指定された場合は、nullptrを返す。\n
   * areaにnullptrを指定された場合は、nullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the view content state allocated to the area
   * of the last arbitration.
   * @param area Area
   * @return The view content state allocated to the area.
   * @details
   *　Even if the area is hidden, Returns the allocated content state.\n
   * If no visible view content state is allocated the area, nullptr is returnd.\n
   * If area is not defined in the Model or nullptr, returns nullptr.
   * @endcond
   */
  virtual const RBAViewContentState* getViewContentState(const RBAArea* area) const=0;

  /**
   * @cond japanese
   * @brief ゾーンに割り当たっている音声コンテントステートを取得する
   * @param zone ゾーン
   * @return ゾーンに割り当たっている音声コンテントステート
   * @details
   * ゾーンがミュートされている場合も、割り当たっている音声コンテントステートを返す。\n
   * zoneに音声コンテントステートが割り当てられていない場合は、nullptrを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないzoneを指定された場合は、nullptrを返す。\n
   * zoneにnullptrを指定された場合は、nullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the sounding sound content state assigned to the zone
   * of the last arbitration.
   * @param zone Zone
   * @return The sounding sound content state assign to the zone.
   * @details
   *　Even if the zone is muted, Returns the allocated content state.\n
   * If no sounding sound content state is allocated the area,
   * nullptr is returnd.\n
   * If zone is not defined in the Model or nullptr, returns nullptr.
   * @endcond
   */
  virtual const RBASoundContentState* getSoundContentState(const RBAZone* zone) const=0;

  // [Hidden/Mute check]

  /**
   * @cond japanese
   * @brief エリアが隠蔽状態であるかチェックする
   * @param area チェックするエリア
   * @return true:隠蔽状態である
   * @return false:隠蔽状態でない
   * @details
   * エリアが隠蔽状態ならtrueを返す。\n
   * 隠蔽状態とは、制約式によってそのエリアが隠蔽状態でなければならない、と制約されている
   * 状態を指す。\n
   * コンテントが割り当てられていなくても、隠蔽状態であればtrueを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないareaを指定された場合は、falseを返す。\n
   * areaにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the area is hidden state of the last arbitration.\n
   * The hidden state is a state in which the area must be hidden by a
   * constraint expression.\n
   * In the hidden state, it returns true even if the content is not assigned.
   * @param area Reference area to be checked.
   * @return true: Hidden
   * @return false: Not hidden
   * @details
   * If area is not defined in the Model or nullptr, returns nullptr.
   * @endcond
   */
  virtual bool isHidden(const RBAArea* area) const=0;

  /**
   * @cond japanese
   * @brief ゾーンがミュート状態であるかチェックする
   * @param zone チェックするゾーン
   * @return true:ミュート状態である
   * @return false:ミュート状態でない
   * @details
   * ゾーンがミュート状態ならtrueを返す。\n
   * ミュート状態とは、制約式によってそのゾーンがミュート状態でなければならない、
   * と制約されている状態を指す。\n
   * コンテントが割り当てられていなくても、ミュート状態であればtrueを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないzoneを指定された場合は、falseを返す。\n
   * zoneにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the zone is muted state of the last arbitration.\n
   * The muted state is a state in which the zone must be muted by a
   * constraint expression.\n
   * In the muted state, it returns true even if the content is not assigned.
   * @param zone Reference zone to be checked.
   * @return true: Muted
   * @return false: Not muted
   * @details
   * If zone is not defined in the Model or nullptr, returns nullptr.
   * @endcond
   */
  virtual bool isMute(const RBAZone* zone) const=0;

  // [Check Attenuated]

  /**
   * @cond japanese
   * @brief ゾーンが減衰出力状態であるかチェックする
   * @param zone チェックするゾーン
   * @return true:減衰出力状態である
   * @return false:減衰出力状態でない
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がないzoneを指定された場合は、falseを返す。\n
   * zoneにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the zone is attenuated
   * of the last arbitration.
   * @param zone Reference zone to be check.
   * @return true: Attenuated
   * @return false: Not attenuated
   * @details
   * If zone is not defined in the Model or nullptr, returns nullptr.
   * @endcond
   */
  virtual bool isAttenuated(const RBAZone* zone) const=0;

  // [Cancel check]

  /**
   * @cond japanese
   * @brief 表示コンテントステートが調停負けによりキャンセルされたかチェックする
   * @param state チェックする表示コンテントステート
   * @return true:キャンセルされた
   * @return false:キャンセルされていない
   * @details
   * stateに調停処理前に表示要求がなかった表示コンテントステートを指定された場合は、falseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、falseを返す。\n
   * stateにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the view content state is canceled
   * at the last arbitration.
   * @param state Reference view content state to be checked.
   * @return true: Canceled
   * @return false: Not canceled or Not request view content state
   * @details
   * If state is not active, returns false.\n
   * If state is not defined in the Model or nullptr, returns false.
   * @endcond
   */
  virtual bool isCancel(const RBAViewContentState* state) const=0;

  /**
   * @cond japanese
   * @brief 音声コンテントステートが調停負けによりキャンセルされたかチェックする
   * @param state チェックする音声コンテントステート
   * @return true:キャンセルされた
   * @return false:キャンセルされていない
   * @details
   * stateに調停処理前に出力要求がなかった音声コンテントステートを指定された場合は、falseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、falseを返す。\n
   * stateにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the sound content state is canceled
   * at the last arbitration.
   * @param state Reference view content state to be checked.
   * @return true: Canceled
   * @return false: Not canceled
   * @details
   * If state is not active, returns false.\n
   * If state is not defined in the Model or nullptr, returns false.
   * @endcond
   */
  virtual bool isCancel(const RBASoundContentState* state) const=0;

  // common

  /**
   * @cond japanese
   * @brief 表示状態の変化情報(ビューアクション)を取得する
   * @return ビューアクションのリスト
   * @details
   * 前回の調停結果と今回の調停結果で表示状態が変化した情報をViewActionとして取得する。\n
   * 表示状態の変化では隠蔽と非表示は区別しない。\n
   * @endcond
   *
   * @cond english
   * @brief Returns information of view status changes
   * (the view actions) of the last arbitration.
   * @return List of view actions.
   * @details
   * ViewAction is an information of differences \n
   * between the last arbitration result and its previous result.\
   * There is no difference between hidden and not displayed for visible status.\n
   * @endcond
   */
  virtual const std::list<const RBAViewAction*>& getViewActions() const=0;

  /**
   * @cond japanese
   * @brief 調停結果ステータスを取得する
   * @return SUCCESS:処理成功
   * @return UNKNOWN_CONTENT_STATE:コンテキストが未定義
   * @return CANCEL_ERROR:調停処理の差し戻しエラー
   * @endcond
   *
   * @cond english
   * @brief Returns the result status type of the last arbitration.
   * @return SUCCESS: Success
   * @return UNKNOWN_CONTENT_STATE: Failed (The reuqest is unknown)
   * @return CANCEL_ERROR: Cancel arbitrration error
   * @endcond
   */
  virtual RBAResultStatusType getStatusType() const=0;

  /**
   * @cond japanese
   * @brief 全オンライン制約式のチェック結果を取得する
   * @return true:全てのオンライン制約式の評価結果がOKとなり、調停終了した
   * @return false:オンライン制約式の評価結果にNGが含まれたまま調停終了した
   * @endcond
   *
   * @cond english
   * @brief Returns satisfied status of all online constraints.
   * @return true:All online constraints check result is OK, and arbitration finished.
   * @return false:All online constraints check result is NG, and arbitration finished.
   * @endcond
   */
  virtual bool satisfiesConstraints() const=0;

  /**
   * @cond japanese
   * @brief シーンのプロパティ値を取得する
   * @param scene シーン
   * @param propertyName シーンのプロパティ名
   * @return シーンのプロパティ値
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がないsceneを指定された場合は、-99を返す。\n
   * propertyNameにモデルに定義がないプロパティ名を指定された場合は-99を返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the property value of scene.
   * @return Property value
   * @details
   * If the scene or propertyName is not defined in the Model, returns -99.\n
   * @endcond
   */
  virtual std::int32_t getSceneProperty(const RBAScene* scene, const std::string& propertyName) const=0;

  // internal {
  /**
   * @cond japanese
   * @brief 前回の調停結果で、表示状態となっていたエリアを取得する
   * @return 表示エリアのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the displaying areas of the previous arbitration.
   * @return List of visible areas.
   * @endcond
   */
  virtual const std::list<const RBAArea*>& getPreVisibleAreas() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、出力状態となっていたゾーンを取得する
   * @return 前回の調停結果で、出力状態となっていたゾーンのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the outputting sounding zones of the previous arbitration.
   * @return List of sounding zones.
   * @endcond
   */
  virtual const std::list<const RBAZone*>& getPreSoundingZones() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、表示状態となっていた表示コンテントステートを取得する
   * @return 前回の調停結果で、表示状態となっていた表示コンテントステートのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the view content states to be displayed of the previous arbitration.
   * @return List of visible view content states.
   * @endcond
   */
  virtual const std::list<const RBAViewContentState*>& getPreVisibleContentStates() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、出力状態となっていた音声コンテントステートを取得する
   * @return 前回の調停結果で、出力状態となっていた音声コンテント状態のリスト
   * @details 減衰出力状態となっていた音声コンテントステートも取得される
   * @endcond
   *
   * @cond english
   * @brief Returns the sound content states to be outputted of the previous arbitration.
   * @return List of sounding sound content states.
   * @details The list contains attenuated content states.
   * @endcond
   */
  virtual const std::list<const RBASoundContentState*>& getPreSoundingContentStates() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、表示要求状態だった表示コンテントステートを取得する
   * @return 前回の調停結果で、表示要求状態だった表示コンテントステートのリスト
   * @details
   * 表示要求状態の表示コンテントステートは、これまでに表示要求のあった表示コンテントステートの累積であり、
   * 表示取り下げ要求や、負け時アクションにより表示要求がキャンセルされたコンテントステートは含まない。
   * @endcond
   *
   * @cond english
   * @brief Returns the active view content states of the previous arbitration
   * result.
   * @return List of active view content states.
   * @details
   * The active view content states are those that have been requested to
   * display so far.　They do not include the view content state whose request
   * has been withdrawn or canceled.
   *
   * @endcond
   */
  virtual const std::list<const RBAViewContentState*>& getPreActiveViewContentStates() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、出力要求状態だった音声コンテントステートを取得する
   * @return 前回の調停結果で、出力要求状態だった音声コンテントステートのリスト
   * @details
   * 出力要求状態の音声コンテントステートは、これまでに出力要求のあった音声コンテントステートの累積であり、
   * 出力取り下げ要求や、負け時アクションにより出力要求がキャンセルされたコンテントステートは含まない。
   * @endcond
   *
   * @cond english
   * @brief Returns the active sound content states of the previous arbitration
   * result.
   * @return List of active sound content states.
   * @details
   * The active sound content states are those that have been requested to
   * output so far.　They do not include the sound content state whose request
   * has been withdrawn or canceled.
   *
   * @endcond
   */
  virtual const std::list<const RBASoundContentState*>& getPreActiveSoundContentStates() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、ON状態だったシーンを取得する
   * @return 前回の調停結果で、ON状態だったシーンのリスト
   * @details
   * ON状態のシーンは、これまでにシーンONを通知されたシーンや、制御実行式でON状態となったシーンの累積であり、
   * その後OFF要求のあったシーンや制御実行式でOFF状態となったシーンは含まない。
   * @endcond
   *
   * @cond english
   * @brief Returns the active scenes of the previous arbitration.
   * @return List of active scenes.
   * @details
   * The active scenes are those that have been requested for ON so far.
   * They do not include scenes requested for OFF afterwards.
   *
   * @endcond
   */
  virtual const std::list<const RBAScene*>& getPreActiveScenes() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、非表示だったエリアを取得する
   * @return 前回の調停結果で、非表示だった非表示エリアのリスト
   * @details
   * すべてのエリアのうち表示されていないエリアを返す。\n
   * 隠蔽されているエリアも取得される。
   * @endcond
   *
   * @cond english
   * @brief Returns the invisible areas of the previous arbitration.
   * @return List of invisible areas.
   * @details
   * Returns the areas which are not displayed out of all areas.
   * @endcond
   */
  virtual const std::list<const RBAArea*>& getPreInvisibleAreas() const=0;

  /*
   * @cond japanese
   * @brief 前回の調停結果で、非出力だったゾーンを取得する
   * @return 前回の調停結果で、非出力だったゾーンのリスト
   * @details
   * すべてのゾーンのうち出力されていないゾーンを返す。\n
   * ミュートされているゾーンも取得される。
   * @endcond
   *
   * @cond english
   * @brief Returns the unsounding zones of the previous arbitration.
   * @return List of unsounding zones.
   * @details
   * Returns the zones which are not outputted out of all zones.
   * @endcond
   */
  virtual const std::list<const RBAZone*>& getPreUnsoundingZones() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、隠蔽状態だったエリアを取得する
   * @return 前回の調停結果で、隠蔽状態だったエリアのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the areas which have become invisible at the previous arbitration.
   * @return List of areas.
   *
   * Returns the area which become to be invisible.
   * @endcond
   */
  virtual const std::list<const RBAArea*>& getPreHiddenAreas() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、ミュート状態だったゾーンを取得する
   * @return 前回の調停結果で、ミュート状態だったゾーンのリスト
   * @endcond
   *
   * @cond english
   * @brief Get the muted zones of the previous arbitration.
   * @return List of muted zones.
   *
   * Retuens the zones that is defeted and canceled sound contents.
   * @endcond
   */
  virtual const std::list<const RBAZone*>& getPreMuteZones() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、減衰出力状態だったゾーンを取得する
   * @return 前回の調停結果で、減衰出力状態だったゾーンのリスト
   * @endcond
   *
   * @cond english
   * @brief Returns the attenuated zones of the previous arbitration.
   * @return List of attenuated zones.
   * @endcond
   */
  virtual const std::list<const RBAZone*>& getPreAttenuatedZones() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、調停負けにより表示要求がキャンセルされていた表示コンテントを取得する
   * @return 前回の調停結果で、調停負けにより表示要求がキャンセルされていた表示コンテントのリスト
   * @details
   * 前回の調停処理で、負け時アクションで要求キャンセルされていた表示コンテントを取得する。\n
   * 表示取り下げ要求により、表示要求が取り下げられていたものは取得しない。
   * @endcond
   *
   * @cond english
   * @brief Returns the canceled view contents of the previous arbitration.
   * @return List of canceled view contents.
   * @endcond
   */
  virtual const std::list<const RBAViewContent*>& getPreCanceledViewContents() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、調停負けにより出力要求がキャンセルされていた音声コンテントを取得する
   * @return 前回の調停結果で、調停負けにより出力要求がキャンセルされていた音声コンテントのリスト
   * @details
   * 前回の調停処理で、負け時アクションで要求キャンセルされていた音声コンテントを取得する。\n
   * 出力取り下げ要求により、出力要求が取り下げられていたものは取得しない。
   * @endcond
   *
   * @cond english
   * @brief Returns the canceled sound contents of the previous arbitration.
   * @return List of canceled sound contents.
   * @endcond
   */
  virtual const std::list<const RBASoundContent*>& getPreCanceledSoundContents() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、調停負けにより待機状態となっていた表示コンテントを取得する
   * @return 前回の調停結果で、調停負けにより待機状態となっていた表示コンテントのリスト
   * @details
   * 表示要求があり、エリアに割り当たっていなかった表示コンテントを取得する。
   * 負け時アクションにより、要求がキャンセルされていた表示コンテントや、
   * エリアに割り当たっていたが、エリアが隠蔽されていた表示コンテントは取得しない。
   * @endcond
   *
   * @cond english
   * @brief Returns the stand by view contents due to defeated at the previous
   * arbitration.
   * @return List of stand by view contents.
   * @endcond
   */
  virtual const std::list<const RBAViewContent*>& getPreStandbyViewContents() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、調停負けにより待機状態となっていた音声コンテントを取得する
   * @return 前回の調停結果で、調停負けにより待機状態となっていた音声コンテントのリスト
   * @details
   * 出力要求があり、ゾーンに割り当たっていなかった音声コンテントを取得する。
   * 負け時アクションにより、要求がキャンセルされていた音声コンテントや、
   * ゾーンに割り当たっていたが、ゾーンがミュートされていた音声コンテントは取得しない。
   * @endcond
   *
   * @cond english
   * @brief Returns the stand by sound contents due to defeated at previous
   * arbitration.
   * @return List of stand by sound contents.
   * @endcond
   */
  virtual const std::list<const RBASoundContent*>& getPreStandbySoundContents() const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、エリアに割り当てられていた表示コンテントステートを取得する
   * @param area エリア
   * @return areaに割り当てられていた表示コンテントステート
   * @details
   * areaに表示コンテントステートが割り当てられていなかった場合は、nullptrを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないareaを指定された場合は、nullptrを返す。\n
   * areaにnullptrを指定された場合は、nullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the view content state assigned to the area of the previous
   * arbitration.
   * @param area Area
   * @return The view content state assign to the area.
   *
   * If no view content state is allocated to the area, nullptr is returnd.
   * @endcond
   */
  virtual const RBAViewContentState* getPreContentState(const RBAArea* area) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、ゾーンに割り当てられていた音声コンテントステートを取得する
   * @param zone ゾーン
   * @return zoneに割り当てられていた音声コンテントステート
   * @details
   * zoneに音声コンテントステートが割り当てられていなかった場合は、nullptrを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないzoneを指定された場合は、nullptrを返す。\n
   * zoneにnullptrを指定された場合は、nullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the sound content state assigned to the zone of the previous
   * arbitration.
   * @param zone Zone
   * @return The sound content state assign to the zone.
   *
   * If no sound content state is allocated to the zone, nullptr is returned.
   * @endcond
   */
  virtual const RBASoundContentState* getPreContentState(const RBAZone* zone) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、表示コンテントステートを割り当てていたエリアを取得する
   * @param state 表示コンテントステート
   * @return 前回の調停結果で、表示コンテントステートを割り当てていたエリアのリスト
   * @details
   * 表示コンテントステートがエリアに割り当てられていなかった場合は、空のリストを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、空のリストを返す。\n
   * stateにnullptrを指定された場合は、空のリストを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the area to which the view content state is allocated of the
   * previous arbitration.
   * @param state View content state
   * @return The areas to which the view content state.
   *
   * If the view content state is not assigned to any area, nullptr is returned.
   * @endcond
   */
  virtual const std::list<const RBAArea*> getPreArea(const RBAViewContentState* state) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、音声コンテントステートを割り当てていたゾーンを取得する
   * @param state 音声コンテントステート
   * @return 前回の調停結果で、音声コンテントステートを割り当てていたゾーンのリスト
   * @details
   * 音声コンテントステートがゾーンに割り当てられていなかった場合は、空のリストを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、空のリストを返す。\n
   * stateにnullptrを指定された場合は、空のリストを返す。
   * @endcond
   *
   * @cond english
   * @brief Get the zone to which the sound content state is allocated of the
   * previous arbitration.
   * @param state Sound content state
   * @return The zones to which the sound content state is allocated.
   *
   * If the sound content state is not assigned to any zone,
   * null ptr is retuened.
   * @endcond
   */
  virtual const std::list<const RBAZone*> getPreZone(const RBASoundContentState* state) const=0;

  /**
   * @cond japanese
   * @brief 前回調停結果で、表示コンテントを割り当てていたエリアを取得する
   * @param content 表示コンテント
   * @return 前回調停結果で、表示コンテントを割り当てていたエリアのリスト
   * @details
   * 表示コンテントがエリアに割り当てられていなかった場合は、空のリストを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないcontentを指定された場合は、空のリストを返す。\n
   * contentにnullptrを指定された場合は、空のリストを返す。\n
   * getArea(RBAViewContentState*)との違いは引数の型のみであり、
   * 同じコンテントに対する要求であれば、戻り値は必ず一致する。
   * @endcond
   *
   * @cond english
   * @brief Returns the area to which the view content is allocated of the
   * previous arbitration.
   * @param content View content
   * @return The areas to which the view content is allocated.
   *
   * If the view content is not assigned to any area, nullptr is returned.
   * @endcond
   */
  virtual const std::list<const RBAArea*> getPreArea(const RBAViewContent* content) const=0;

  /**
   * @cond japanese
   * @brief 前回調停結果で、音声コンテントを割り当てていたゾーンを取得する
   * @param content 音声コンテント
   * @return 前回調停結果で、音声コンテントを割り当てていたゾーンのリスト
   * @details
   * 音声コンテントがゾーンに割り当てられていなかった場合は、空のリストを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないcontentを指定された場合は、空のリストを返す。\n
   * contentにnullptrを指定された場合は、空のリストを返す。\n
   * getZone(RBASoundContentState*)との違いは引数の型のみであり、
   * 同じコンテントに対する要求であれば、戻り値は必ず一致する。
   * @endcond
   *
   * @cond english
   * @brief Returns the zone to which the sound content state is allocated of the
   * previous arbitration.
   * @param content Sound content
   * @return The zones to which the sound content is allocated.
   *
   * If the sound content is not assigned to any area, nullptr is returned.
   * @endcond
   */
  virtual const std::list<const RBAZone*> getPreZone(const RBASoundContent* content) const=0;

  /**
   * @cond japanese
   * @brief 前回調停結果での、エリアのサイズを取得する
   * @param area エリア
   * @return 前回調停結果での、エリアのサイズ
   * @details
   * エリアには複数のサイズを定義することができ、そのサイズは表示コンテントに合わせて変化する。\n
   * エリアに割り当たっていた表示コンテントに合わせたサイズを応答する。\n
   * エリアに表示コンテントが割り当てられていなかった場合は、nullptrを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないエリアを指定された場合は、nullptrを返す。\n
   * areaにnullptrを指定された場合は、nullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the size of the area
   * determined in the previous arbitration.
   * @param area Area
   * @return The size of the area.
   * @endcond
   */
  virtual const RBASize* getPreSize(const RBAArea* area) const=0;

  /**
   * @cond japanese
   * @brief 前回調停結果で、シーンがON状態だったかチェックする
   * @param scene ON状態だったかチェックするシーン
   * @return true:ON状態\n
   * false:OFF状態
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がないシーンを指定された場合は、falseを返す。\n
   * sceneにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the scene is active
   * of the previous arbitration.
   * @param scene Reference scene to be checked.
   * @return true: Active
   * @return false: Not active
   *
   * The active scene is the scene requested　to ON.
   * @endcond
   */
  virtual bool isPreActive(const RBAScene* scene) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、表示コンテントが表示要求状態だったかチェックする
   * @param content 表示要求状態だったかチェックする表示コンテント
   * @return true:表示要求状態である
   * @return false:表示要求状態でない
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がない表示コンテントを指定された場合は、falseを返す。\n
   * contentにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the view content is active
   * of the previous arbitration.
   * @param state Reference view content to be checked.
   * @return true: Active
   * @return false: Not active
   *
   * The active view content is the content requested to be displayed.
   * @endcond
   */
  virtual bool isPreActive(const RBAViewContent* content) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、音声コンテントが出力要求状態だったかチェックする
   * @param content 表示要求状態だったかチェックする出力コンテント
   * @return true:出力要求状態である
   * @return false:出力要求状態でない
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がない音声コンテントを指定された場合は、falseを返す。\n
   * contentにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the sound content is active
   * of the previous arbitration.
   * @param state Reference sound content to be checked.
   * @return true: Active
   * @return false: Not active
   *
   * The active sound content is the content requested to be outputted.
   * @endcond
   */
  virtual bool isPreActive(const RBASoundContent* content) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、エリアが表示状態だったかをチェックする
   * @param area チェックするエリア
   * @return true:表示状態である
   * @return false:非表示状態である
   * @details
   * 隠蔽されていたエリアはfalseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないareaを指定された場合は、falseを返す。\n
   * areaにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the area is visible
   * of the previous arbitration.
   * @param area Reference area to be checked.
   * @return true: Visible
   * @return false: Not visible
   * @endcond
   */
  virtual bool isPreVisible(const RBAArea* area) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、ゾーンが出力状態だったかチェックする
   * @param zone チェックするゾーン
   * @return true:出力状態である
   * @return false:非出力状態である
   * @details
   * ミュートされていたエリアはfalseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないzoneを指定された場合は、falseを返す。\n
   * zoneにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the zone is sounding
   * of the previous arbitration.
   * @param zone Reference zone to be checked.
   * @return true: Sounding
   * @return false: Not sounding
   * @endcond
   */
  virtual bool isPreSounding(const RBAZone* zone) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、表示コンテントステートが表示状態だったかチェックする
   * @param state チェックする表示コンテントステート
   * @return true:stateが表示エリアに割り当てられている
   * @return false:stateが表示エリアに割り当てられていない
   * @details
   * 隠蔽されているエリアにのみ割り当てられていた場合はfalseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないareaを指定された場合は、falseを返す。\n
   * stateにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the view content state is visible
   * of the previous arbitration.
   * @param state Reference view content state to be checked.
   * @return true: state is allocated to visible area.
   * @return false: state is not allocated to visible area.
   * @endcond
   */
  virtual bool isPreVisible(const RBAViewContentState* state) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、音声コンテントステートが出力状態だったかチェックする
   * @param state チェックする音声コンテントステート
   * @return true:stateが出力ゾーンに割り当てられている
   * @return false:stateが出力ゾーンに割り当てられていない
   * @details
   * ミュートされているゾーンにのみ割り当てられていた場合はfalseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、falseを返す。\n
   * stateにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the sound content state is sounding
   * of the previous arbitration.
   * @param state Reference sound content state to check.
   * @return true: state is allocated to outputting zone.
   * @return false: state is not allocated to outputting zone.
   * @endcond
   */
  virtual bool isPreSounding(const RBASoundContentState* state) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、ゾーンに割り当たっていた音声コンテントステートを取得する
   * @param zone ゾーン
   * @return ゾーンに割り当たっていた音声コンテントステート
   * @details
   * ゾーンがミュートされていた場合も、割り当たっていた音声コンテントステートを返す。\n
   * zoneに音声コンテントステートが割り当てられていなかった場合は、nullptrを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないzoneを指定された場合は、nullptrを返す。\n
   * zoneにnullptrを指定された場合は、nullptrを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns the sounding sound content state assigned to the zone
   * of the previous arbitration.
   * @param zone Zone
   * @return The sounding sound content state assign to the zone.
   *
   *　When a zone is muted, Returns the content state.
   * If no sounding sound content state is allocated the area,
   * nullptr is returnd.
   * @endcond
   */
  virtual const RBASoundContentState* getPreSoundContentState(const RBAZone* zone) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、エリアが隠蔽状態だったかチェックする
   * @param area チェックするエリア
   * @return true:隠蔽状態である
   * @return false:隠蔽状態でない
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がないareaを指定された場合は、falseを返す。\n
   * areaにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the area is hidden
   * of the previous arbitration.
   * @param area Reference area to be checked.
   * @return true: Hidden
   * @return false: Not hidden
   * @endcond
   */
  virtual bool isPreHidden(const RBAArea* area) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、ゾーンがミュート状態だったかチェックする
   * @param zone チェックするゾーン
   * @return true:ミュート状態である
   * @return false:ミュート状態でない
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がないzoneを指定された場合は、falseを返す。\n
   * zoneにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the zone is muted of the previous arbitration.
   * @param zone Reference zone to be checked.
   * @return true: Muted
   * @return false: Not muted
   * @endcond
   */
  virtual bool isPreMute(const RBAZone* zone) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、ゾーンが減衰出力状態だったかチェックする
   * @param zone チェックするゾーン
   * @return true:減衰出力状態である
   * @return false:減衰出力状態でない
   * @details
   * 調停処理を実施した調停FWにセットされているモデルに定義がないzoneを指定された場合は、falseを返す。\n
   * zoneにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the zone is attenuated
   * of the previous arbitration.
   * @param zone Reference zone to be checked.
   * @return true: Attenuated
   * @return false: Not attenuated
   * @endcond
   */
  virtual bool isPreAttenuated(const RBAZone* zone) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、表示コンテントステートが調停負けによりキャンセルされていたかチェックする
   * @param state チェックする表示コンテントステート
   * @return true:キャンセルされた
   * @return false:キャンセルされていない
   * @details
   * stateに調停処理前に表示要求がなかった表示コンテントステートを指定された場合は、falseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、falseを返す。\n
   * stateにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the view content state is canceled
   * of the previous arbitration.
   * @param state Reference view content state to be checked.
   * @return true: Canceled
   * @return false: Not canceled or Not request view content state
   * @endcond
   */
  virtual bool isPreCancel(const RBAViewContentState* state) const=0;

  /**
   * @cond japanese
   * @brief 前回の調停結果で、音声コンテントステートが調停負けによりキャンセルされていたかチェックする
   * @param state チェックする音声コンテントステート
   * @return true:キャンセルされた
   * @return false:キャンセルされていない
   * @details
   * stateに調停処理前に出力要求がなかった音声コンテントステートを指定された場合は、falseを返す。\n
   * 調停処理を実施した調停FWにセットされているモデルに定義がないstateを指定された場合は、falseを返す。\n
   * stateにnullptrを指定された場合は、falseを返す。
   * @endcond
   *
   * @cond english
   * @brief Returns true if the sound content state is canceled
   * of the previous arbitration.
   * @param state Reference view content state to be checked.
   * @return true: Canceled
   * @return false: Not canceled
   * @endcond
   */
  virtual bool isPreCancel(const RBASoundContentState* state) const=0;

  /**
   * @cond japanese
   * @brief 調停処理のログを取得する
   * @return 調停処理のログ
   * @endcond
   *
   * @cond english
   * @brief Returns the log of the last arbitration.
   * @return Log string
   * @endcond
   */
  virtual std::string getLog() const=0;

  /**
   * @cond japanese
   * @brief ディスプレイの表示状態を取得する
   * @param display チェックするディスプレイ
   * @return true: 何か表示されている
   * @return false: 何も表示されていない
   * @endcond
   */
  virtual bool hasDisplayingArea(const RBADisplay* display) const=0;
  // }

};

}

#endif
