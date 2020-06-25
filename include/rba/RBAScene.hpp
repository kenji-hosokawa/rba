// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * シーンクラス
 */

#ifndef RBASCENE_HPP
#define RBASCENE_HPP

#include <cstdint>
#include <list>
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
 * @class RBAScene
 * システム含むその時の状態を包括的に表現する。<br>
 * シーンによってエリア/ゾーンや表示/音声コンテントの状態を切り替えるために使用する。
 * また、グローバルシーンを定義して、複数のRBAモデル（プロジェクト）間で調停結果を
 * 共有することもできる。
 * @endcond
 *
 * @cond english
 * @class RBAScene
 * Express the state(Including system state) at that time comprehensively.<br>
 * Used scene for switch area/zone and view/sound content state.
 * And plural RBA model(project) can share arbitration result by definitions global scene.
 * @endcond
 */
class RBAScene
{
protected:
  RBAScene()=default;
  RBAScene(const RBAScene&)=delete;
  RBAScene(RBAScene&&)=delete;
  RBAScene& operator=(const RBAScene&)=delete;
  RBAScene& operator=(RBAScene&&)=delete;

public:
  virtual ~RBAScene()=default;

public:
  /**
   * @cond japanese
   * @brief シーン名を取得する
   * @return シーン名
   * @endcond
   *
   * @cond english
   * @brief Returns the scene name
   * @return Scene name
   * @endcond
   */
  virtual std::string getName() const=0;

  /**
   * @cond japanese
   * @brief グローバルシーン定義を取得する　
   * @return true:グローンバルなシーン定義 false:ローカルなシーン定義
   * @endcond
   *
   * @cond english
   * @brief Returns the global scene status.
   * @return global scene status.
   * @endcond
   */
  virtual bool isGlobal() const=0;

  /**
   * @cond japanese
   * @brief プロパティ名リストを取得する
   * @return プロパティ名のリスト
   * @endcond
   *
   * @cond english
   * @brief Returns List of the scene property name.
   * @return List of the scene property name
   * @endcond
   */
  virtual const std::list<std::string>& getPropertyNames() const=0;

  /**
   * @cond japanese
   * @brief プロパティのデフォルト値を取得する
   * @param propertyName プロパティ名
   * @return プロパティのデフォルト値
   *
   * propertyNameが存在しない場合は-1
   * @endcond
   *
   * @cond english
   * @brief Returns Default value of the scene property.
   * @param propertyName Scene property name
   * @return Default value of the scene property
   * @endcond
   */
  virtual std::int32_t getPropertyValue(const std::string& propertyName) const=0;

};

}

#endif
