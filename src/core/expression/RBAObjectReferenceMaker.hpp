/// @file  RBAObjectReferenceMaker.hpp
/// @brief ObjectReferenceオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAOBJECTREFERENCEMAKER_HPP
#define RBAOBJECTREFERENCEMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

/// @brief ObjectReferenceオブジェクト生成クラス
class DLL_EXPORT RBAObjectReferenceMaker : public RBAExpressionMaker
{
public:
  explicit RBAObjectReferenceMaker(const std::string& label="ObjectReference");
  RBAObjectReferenceMaker(const RBAObjectReferenceMaker&)=delete;
  RBAObjectReferenceMaker(const RBAObjectReferenceMaker&&)=delete;
  RBAObjectReferenceMaker& operator=(const RBAObjectReferenceMaker&)=delete;
  RBAObjectReferenceMaker& operator=(const RBAObjectReferenceMaker&&)=delete;
  virtual ~RBAObjectReferenceMaker()=default;

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
                                       RBAModelElement* owner) override;
  
};

}

#endif
