// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * ビューアクションクラス
 */

#ifndef RBAVIEWACTION_HPP
#define RBAVIEWACTION_HPP

#include "RBAViewActionType.hpp"

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

namespace rba {

class RBAArea;
class RBAViewContent;
class RBAViewContentState;

/**
 * @cond japanese
 * @class RBAViewAction
 * 表示コンテントの変化を定義する。<br>
 * 表示コンテントの変化は、エリアに対して表示コンテントが変化するコンテント遷移、
 * 表示コンテントが表示されるエリアが変化するコンテント移動がある。
 * @endcond
 *
 * @cond english
 * @class RBAViewAction
 * Define the change information of view contents.<br>
 * Change information has 2 type.
 * The contents transition, that view contents change for an area.
 * The contents move, that the view content displayed area changes.
 * @endcond
 */
class DLL_EXPORT RBAViewAction
{
public:
  RBAViewAction()=default;
  RBAViewAction(RBAViewAction&&)=delete;
  RBAViewAction& operator=(const RBAViewAction&)=delete;
  RBAViewAction& operator=(RBAViewAction&&)=delete;
  virtual ~RBAViewAction()=default;

protected:
  //コピーコンストラクタは他クラスで使用しているためdefaultで定義
  RBAViewAction(const RBAViewAction&)=default;

public:
  /**
   * @cond japanese
   * @brief コンテント遷移のエリアを取得
   * @return コンテント遷移のエリア
   * @endcond
   *
   * @cond english
   * @brief Returns the area of the contents transition.
   * @return Area of the contents transition
   * @endcond
   */
  virtual const RBAArea* getArea() const;

  /**
   * @cond japanese
   * @brief コンテント遷移の置き換え(TRANSITION_REPLACE)における、
   *        前に表示されていた表示コンテントを取得
   * @return 前に表示されていた表示コンテント
   *
   * * getViewActionType() == TRANSITION_REPLACE以外はnullptrを返す
   *
   * @endcond
   *
   * @cond english
   * @brief Returns previously displayed the view content.
   * Used when change information type is the contents transition(TRANSITION_REPLACE).
   * @return Previously displayed the view content
   *
   * * If the change information type is not the contents transition(TRANSITION_REPLACE), returns nullptr.
   *
   * @endcond
   */
  virtual const RBAViewContent* getFromContent() const;

  /**
   * @cond japanese
   * @brief コンテント遷移の置き換え(TRANSITION_REPLACE)における、
   *        今回に表示する表示コンテントを取得
   * @return 今回表示する表示コンテント
   *
   * * getViewActionType() == TRANSITION_REPLACE以外はnullptrを返す
   *
   * @endcond
   *
   * @cond english
   * @brief Returns subsequently displayed the view content.
   * Used when change information type is the contents transition(TRANSITION_REPLACE).
   * @return Subsequently displayed the view content.
   *
   * * If the change information type is not the contents transition(TRANSITION_REPLACE), returns nullptr.
   *
   * @endcond
   */
  virtual const RBAViewContent* getToContent() const;

  /**
   * @cond japanese
   * @brief コンテント遷移の置き換え(TRANSITION_REPLACE)における、
   *        前に表示されていた表示コンテント状態を取得
   * @return 前に表示されていた表示コンテント状態
   * @endcond
   *
   * * getViewActionType() == TRANSITION_REPLACE以外はnullptrを返す
   *
   * @cond english
   * @brief Returns previously displayed the view content state.
   * Used when change information type is the contents transition(TRANSITION_REPLACE).
   * @return Previously displayed the view content state
   *
   * * If the change information type is not the contents transition(TRANSITION_REPLACE), returns nullptr.
   *
   * @return 
   * @endcond
   */
  virtual const RBAViewContentState* getFromContentState() const;

  /**
   * @cond japanese
   * @brief コンテント遷移の置き換え(TRANSITION_REPLACE)における、
   *        今回に表示する表示コンテント状態を取得
   * @return 今回表示する表示コンテント状態
   *
   * * getViewActionType() == TRANSITION_REPLACE以外はnullptrを返す
   *
   * @endcond
   *
   * @cond english
   * @brief Returns subsequently displayed the view content state.
   * Used when change information type is the contents transition(TRANSITION_REPLACE).
   * @return Subsequently displayed the view content state.
   *
   * * If the change information type is not the contents transition(TRANSITION_REPLACE), returns nullptr.
   *
   * @endcond
   */
  virtual const RBAViewContentState* getToContentState() const;

  /**
   * @cond japanese
   * @brief コンテント移動(MOVE)における、移動前のエリアを取得
   * @return コンテント移動前のエリア
   *
   * * getViewActionType() == MOVE以外はnullptrを返す
   *
   * @endcond
   *
   * @cond english
   * @brief Returns previously displayed the area.
   * Used when change information type is the contents move(MOVE).
   * @return Previously displayed the area
   *
   * * If the change information type is not the contents move(MOVE), returns nullptr.
   *
   * @endcond
   */
  virtual const RBAArea* getFromArea() const;

  /**
   * @cond japanese
   * @brief コンテント移動(MOVE)における、移動後のエリアを取得
   * @return コンテント移動後のエリア
   *
   * * getViewActionType() == MOVE以外はnullptrを返す
   *
   * @endcond
   *
   * @cond english
   * @brief Returns subsequently displayed the area.
   * Used when change information type is the contents move(MOVE).
   * @return Subsequently displayed the area
   *
   * * If the change information type is not the contents move(MOVE), returns nullptr.
   *
   * @endcond
   */
  virtual const RBAArea* getToArea() const;

  /**
   * @cond japanese
   * @brief ビューアクションにおけるコンテントを取得
   * @return 表示コンテント
   *
   * * getViewActionType() == TRANSITION_ADDの場合は、表示する表示コンテントを返す
   * * getViewActionType() == TRANSITION_REMOVEの場合は、非表示にする表示コンテントを返す
   * * getViewActionType() == TRANSITION_REPLACEの場合は、nullptrを返す
   * * getViewActionType() == MOVEの場合は、エリアを変更する表示コンテントを返す
   *
   * @endcond
   *
   * @cond english
   * @brief Returns view content of change information.
   * @return View content of change information
   *
   * * If getViewActionType() == TRANSITION_ADD, returns display view content.
   * * If getViewActionType() == TRANSITION_REMOVE, returns hide view content.
   * * If getViewActionType() == TRANSITION_REPLACE, returns nullptr.
   * * If getViewActionType() == MOVE, returns view content which changes the area.
   *
   * @endcond
   */
  virtual const RBAViewContent* getContent() const;

  /**
   * @cond japanese
   * @brief ビューアクションにおける表示コンテントの状態を取得
   * @return 表示コンテントの状態
   *
   * * getViewActionType() == TRANSITION_ADDの場合は、表示する表示コンテントの状態を返す
   * * getViewActionType() == TRANSITION_REMOVEの場合は、非表示にする表示コンテントの状態を返す
   * * getViewActionType() == TRANSITION_REPLACEの場合は、nullptrを返す
   * * getViewActionType() == MOVEの場合は、エリアを変更する表示コンテントの状態を返す
   *
   * @endcond
   *
   * @cond english
   * @brief Returns view content state of change information.
   * @return View content state of change information
   *
   * * If getViewActionType() == TRANSITION_ADD, returns display view content state.
   * * If getViewActionType() == TRANSITION_REMOVE, returns hide view content state.
   * * If getViewActionType() == TRANSITION_REPLACE, returns nullptr.
   * * If getViewActionType() == MOVE, returns view content state which changes the area.
   *
   * @endcond
   */
  virtual const RBAViewContentState* getContentState() const;

  /**
   * @cond japanese
   * @brief ビューアクションタイプを返す
   * @return ビューアクションタイプ
   * @endcond
   *
   * @cond english
   * @brief Returns view action type.
   * @return View action type
   * @endcond
   */
  virtual RBAViewActionType getViewActionType() const=0;

  /**
   * @cond japanese
   * @brief ビューアクション比較
   * @return true: 一致している false:一致しない
   * @endcond
   *
   * @cond english
   * @brief Equal operator
   * @return true: equal
   * @return false: not equal
   * @endcond
   */
  virtual bool operator==(const RBAViewAction& viewAction)=0;

};

}

#endif
