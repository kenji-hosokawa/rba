/// @file  RBAModelElementMaker.hpp
/// @brief モデルオブジェクト生成の抽象クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAMODELELEMENTMAKER_HPP
#define RBAMODELELEMENTMAKER_HPP

#include <memory>
#include <string>
#include "RBADllExport.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief ModelElementMakerオブジェクト生成クラス
class DLL_EXPORT RBAModelElementMaker
{
public:
  /// @brief ラベルを指定コンストラクタ
  /// @details ラベルを設定して生成する
  /// @param[in] label 設定するラベル
  RBAModelElementMaker()=default;
  explicit RBAModelElementMaker(const std::string& label);
  virtual ~RBAModelElementMaker()=default;

protected:
  RBAModelElementMaker(const RBAModelElementMaker& maker)=delete;
  RBAModelElementMaker& operator=(const RBAModelElementMaker& maker)=delete;
  // RBAAbstractModelTable::addMaker()でmoveを使用
  RBAModelElementMaker(RBAModelElementMaker&&)=default;
  RBAModelElementMaker& operator=(RBAModelElementMaker&&)=default;

public:
  /// @brief モデルファクトリを設定する
  /// @param[in] モデルファクトリ
  void setFactory(RBAModelFactory* const factory);

  /// @brief ラベルの取得
  /// @details 対応するJSONエレメントのラベルを返す
  /// @return ラベルの文字列
  const std::string& getLabel() const;

  /// @brief ModelElementオブジェクト生成
  /// @details ModelElementオブジェクトを生成して、unique_ptrをmodelに登録する。
  /// @param[in] jsonElem ModelElementのJSONエレメント
  /// @param[in] model 生成したオブジェクトを保存するモデル
  /// @param[in,out] owner 親オブジェクト（未使用）
  /// @return ModelElementオブジェクト
  virtual RBAModelElement* create(const RBAJsonElement* jsonElem,
                                  RBAModelImpl* model,
                                  RBAModelElement* owner=nullptr);

  /// @brief インスタンス取得
  /// @details modelからnameに該当するelementを取得する。名前なしまたはmodelにない場合はインスタンスを生成しmodelに登録する。
  /// @return ModelElementオブジェクト
  virtual RBAModelElement* getInstance(RBAModelImpl* model,
                                       const std::string& name="",
                                       RBAModelElement* owner=nullptr);

  /// @brief Maker登録
  /// @details JSONで使われるクラス名と対応するMakerをマップに登録する
  /// @return なし
  static void addMaker(const std::string& typeName, std::unique_ptr<RBAModelElementMaker> maker);

  /// @brief Maker取得
  /// @details クラス名に対応するMakerをマップから取得する
  /// @return 対応するMaker。存在しない場合はnullを返す。
  static RBAModelElementMaker* getMaker(const std::string& typeName);

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  virtual std::unique_ptr<RBAModelElement> createInstance(const std::string& name="")=0;

  /// @brief 派生クラスごとにモデルエレメントの属性をセットする
  /// @param[in] jsonElem ModelElementのJSONエレメント
  /// @param[in] model 生成したオブジェクトを保存するモデル
  /// @param[in,out] owner 親オブジェクト（未使用）
  virtual RBAModelElement* setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner=nullptr)=0;

  /// @brief モデルファクトリ取得
  /// @details モデルファクトリを取得する
  /// @return モデルファクトリ
  RBAModelFactory* getFactory() const;

private:
  /// @brief Expressionオブジェクト再帰的にオブジェクト生成を行うためのファクトリ
  RBAModelFactory* factory_;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  /// @brief 対応するJSONエレメントのラベル
  const std::string label_;

  /// @brief JSONで使われるクラスを表す文字列と各Makerの対応表
  static std::unordered_map<std::string, std::unique_ptr<RBAModelElementMaker>> makerMap_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
