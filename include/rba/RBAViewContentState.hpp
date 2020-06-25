// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * 表示コンテント状態クラス
 */

#ifndef RBAVIEWCONTENTSTATE_HPP
#define RBAVIEWCONTENTSTATE_HPP

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

class RBAViewContent;

/**
 * @cond japanese
 * @class RBAViewContentState
 * 表示コンテントの状態を定義する。
 * @endcond
 *
 * @cond english
 * @class RBAViewContentState
 * Define the state of view contents.
 * @endcond
 */
class DLL_EXPORT RBAViewContentState
{
protected:
  RBAViewContentState()=default;
  RBAViewContentState(const RBAViewContentState&)=delete;
  RBAViewContentState(RBAViewContentState&&)=delete;
  RBAViewContentState& operator=(const RBAViewContentState&)=delete;
  RBAViewContentState& operator=(RBAViewContentState&&)=delete;
  ~RBAViewContentState()=default;

public:
  /**
   * @cond japanese
   * @brief 表示コンテントの状態名を取得する
   * @return 表示コンテント状態名
   * @endcond
   *
   * @cond english
   * @brief Returns the name of the view contents state.
   * @return view contents state name.
   * @endcond
   */
  virtual std::string getName() const=0;

  /**
   * @cond japanese
   * @brief プライオリティを取得する
   * @return プライオリティ値
   * @endcond
   *
   * @cond english
   * @brief Returns the priority.
   * @return priority value
   * @endcond
   */
  virtual std::int32_t getPriority() const=0;

  /**
   * @cond japanese
   * @brief 表示コンテントを取得する
   * @return 表示コンテント
   * @endcond
   *
   * @cond english
   * @brief Returns the view content.
   * @return view content
   * @endcond
   */
  virtual const RBAViewContent* getOwner() const=0;

  /**
   * @cond japanese
   * @brief オーダーを取得する
   * @return オーダー値
   * @detail \n
   * 表示コンテント状態のオーダーは、表示要求により表示コンテント状態が登録された順番を
   * 示す数値である。
   * オーダー値は1から開始され順にインクリメントされる整数値であり、
   * 非アクティブな表示コンテント状態のオーダー値は0にセットされる。\n
   * 表示コンテント状態と音声コンテント状態のオーダーは、それぞれ別々に割り振られる。
   * @endcond
   *
   * @cond english
   * @brief Returns the order.
   * @return order value
   * @detail The order is a number of sequence of the entry view content state
   * by request. The order value is an integer value starting from 1 and
   * incremented in order, and the order value of the view content state
   * without view request is set to 0.\n
   * The order of the view content state does not include the output request
   * of the sound content state.
   * @endcond
   */
  virtual std::int32_t getOrder() const=0;

  /**
   * @cond japanese
   * @brief 表示コンテント状態を示すユニークな文字列を取得する
   * @return ユニークな文字列
   *
   * ユニークな文字列は、
   * 表示コンテント名＋CONTEXT_SEPARATER＋表示コンテント状態名で構成する。
   * ユニークな文字列は、コンテキスト名として使用している。
   * @endcond
   *
   * @cond english
   * @brief Returns the unique character string of the view contents state.
   * @return Unique character string of the view contents state.
   *
   * Unique character string is
   * view content name + CONTEXT_SEPARATER + view content state name.
   * Use the unique character string as a context name.
   * @endcond
   */
  virtual std::string getUniqueName() const=0;

  /**
   * @cond japanese
   * @brief コンテキスト名から表示コンテント名を取得する
   * @param context コンテキスト名
   * @return 表示コンテント名
   * @endcond
   *
   * @cond english
   * @brief Returns the name of the view content from context name.
   * @param context the context name
   * @return name of the view content
   * @endcond
   */
  static std::string getContentNameByContext(const std::string& context);

  /**
   * @cond japanese
   * @brief コンテキスト名から表示コンテント状態名を取得する
   * @param context コンテキスト名
   * @return 表示コンテント状態名
   * @endcond
   *
   * @cond english
   * @brief Returns the state of the view content from context name.
   * @param context the context name
   * @return state of the view content
   * @endcond
   */
  static std::string getContentStateNameByContext(const std::string& context);

  /**
   * @cond japanese
   * @brief 与えられた文字列がユニーク名（コンテキスト名）かチェックする
   * @param context チェックする文字列
   * @return true:ユニーク名（コンテキスト名）である
   * @return false:ユニーク名（コンテキスト名）でない
   * @endcond
   *
   * @cond english
   * @brief Check if argument is The unique character string(context name).
   * @param context the context name
   * @return true: unique character string(context name)
   * @return false: Not unique character string(context name)
   * @endcond
   */
  static bool isUniqueName(const std::string& context);

public:
  /**
   * @cond japanese
   * @brief プライオリティのデフォルト値
   * @endcond
   *
   * @cond english
   * @brief Defines the default priority value.
   * @endcond
   */
  const static std::int32_t PRIORITY_EDEFAULT = 0;

  /**
   * @cond japanese
   * @brief コンテキスト名を作る時の、表示コンテント名と状態名を接続する文字
   * 接続する文字
   * @endcond
   *
   * @cond english
   * @brief Defines the separator for separating view content name and view content state name.
   * And be the character to connect it.
   * @endcond
   */
  const static char CONTEXT_SEPARATER = '/';

};

}

#endif
