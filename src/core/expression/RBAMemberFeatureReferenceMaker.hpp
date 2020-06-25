/// @file  RBAMemberFeatureReferenceMaker.hpp
/// @brief プロパティのObjectReferenceオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAMEMBERFEATUREREFERENCEMAKER_HPP
#define RBAMEMBERFEATUREREFERENCEMAKER_HPP

#include "RBAObjectReferenceMaker.hpp"

namespace rba
{

class RBARuleObject;

/// @brief プロパティのObjectReferenceオブジェクト生成クラス
class RBAMemberFeatureReferenceMaker : public RBAObjectReferenceMaker
{
public:
  RBAMemberFeatureReferenceMaker();
  RBAMemberFeatureReferenceMaker(const RBAMemberFeatureReferenceMaker&)=delete;
  RBAMemberFeatureReferenceMaker(const RBAMemberFeatureReferenceMaker&&)=delete;
  RBAMemberFeatureReferenceMaker& operator=(const RBAMemberFeatureReferenceMaker&)=delete;
  RBAMemberFeatureReferenceMaker& operator=(const RBAMemberFeatureReferenceMaker&&)=delete;
  virtual ~RBAMemberFeatureReferenceMaker()=default;

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
private:
  const RBARuleObject* getRuleObject(const RBAJsonElement* const jsonElem,
                                     RBAModelImpl* const model);
};

}

#endif
