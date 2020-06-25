/// @file  RBASizeMaker.hpp
/// @brief Sizeオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBASIZEMAKER_HPP
#define RBASIZEMAKER_HPP

#include "RBAModelElementMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief Sizeオブジェクト生成クラス
class RBASizeMaker : public RBAModelElementMaker
{
public:
  RBASizeMaker();
  RBASizeMaker(const RBASizeMaker&)=delete;
  RBASizeMaker(const RBASizeMaker&&)=delete;
  RBASizeMaker& operator=(const RBASizeMaker&)=delete;
  RBASizeMaker& operator=(const RBASizeMaker&&)=delete;
  virtual ~RBASizeMaker()=default;

public:
  /// @brief ModelElementオブジェクト生成
  /// @details ModelElementオブジェクトを生成して、unique_ptrをmodelに登録する。
  /// @param[in] jsonElem ModelElementのJSONエレメント
  /// @param[in] model 生成したオブジェクトを保存するモデル
  /// @param[in,out] owner 親オブジェクト（未使用）
  /// @return ModelElementオブジェクト
  RBAModelElement* create(const RBAJsonElement* jsonElem,
                          RBAModelImpl* model,
                          RBAModelElement* owner=nullptr) override;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

  /// @brief 派生クラスごとにモデルエレメントの属性をセットする
  /// @param[in] jsonElem ModelElementのJSONエレメント
  /// @param[in] model 生成したオブジェクトを保存するモデル
  /// @param[in,out] owner 親オブジェクト（未使用）
  RBAModelElement* setProperty(RBAModelElement* element,
                               const RBAJsonElement* jsonElem,
                               RBAModelImpl* model,
                               RBAModelElement* owner=nullptr) override;

};

}

#endif
