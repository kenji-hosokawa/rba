/// @file  RBAForAllOperatorMaker.hpp
/// @brief ForAllOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAFORALLOPERATORMAKER_HPP
#define RBAFORALLOPERATORMAKER_HPP

#include "RBALambdaContextMaker.hpp"

namespace rba
{

/// @brief ForAllOperatorオブジェクト生成クラス
class RBAForAllOperatorMaker : public RBALambdaContextMaker
{
public:
  RBAForAllOperatorMaker();
  RBAForAllOperatorMaker(const RBAForAllOperatorMaker&)=delete;
  RBAForAllOperatorMaker(const RBAForAllOperatorMaker&&)=delete;
  RBAForAllOperatorMaker& operator=(const RBAForAllOperatorMaker&)=delete;
  RBAForAllOperatorMaker& operator=(const RBAForAllOperatorMaker&&)=delete;
  virtual ~RBAForAllOperatorMaker()=default;

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

  /// @brief LambdaContextの空のオブジェクト生成
  /// @details 派生クラスでunique_ptrの空のオブジェクトを生成する。
  /// @return LambdaContextオブジェクトのunique_ptr
  std::unique_ptr<RBALambdaContext> createLambdaContext() override;

};

}

#endif
