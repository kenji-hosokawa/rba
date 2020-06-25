/// @file  RBASoundContentStateMaker.hpp
/// @brief SoundContentStateオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBASOUNDCONTENTSTATEMAKER_HPP
#define RBASOUNDCONTENTSTATEMAKER_HPP

#include "RBAContentStateMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief SoundContentStateオブジェクト生成クラス
class RBASoundContentStateMaker : public RBAContentStateMaker
{
public:
  RBASoundContentStateMaker();
  RBASoundContentStateMaker(const RBASoundContentStateMaker&)=delete;
  RBASoundContentStateMaker(const RBASoundContentStateMaker&&)=delete;
  RBASoundContentStateMaker& operator=(const RBASoundContentStateMaker&)=delete;
  RBASoundContentStateMaker& operator=(const RBASoundContentStateMaker&&)=delete;
  virtual ~RBASoundContentStateMaker()=default;

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
