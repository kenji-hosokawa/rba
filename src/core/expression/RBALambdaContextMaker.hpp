/// @file  RBALambdaContextMaker.hpp
/// @brief LambdaContextオブジェクト生成抽象クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBASETOPERATORMAKER_HPP
#define RBASETOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBALambdaContext;

/// @brief LambdaContextオブジェクト生成クラス
class RBALambdaContextMaker : public RBAOperatorMaker
{
public:
  explicit RBALambdaContextMaker(const std::string& label="");
  RBALambdaContextMaker(const RBALambdaContextMaker&)=delete;
  RBALambdaContextMaker(const RBALambdaContextMaker&&)=delete;
  RBALambdaContextMaker& operator=(const RBALambdaContextMaker&)=delete;
  RBALambdaContextMaker& operator=(const RBALambdaContextMaker&&)=delete;
  virtual ~RBALambdaContextMaker()=default;

protected:
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
  virtual std::unique_ptr<RBALambdaContext> createLambdaContext()=0;

};

}

#endif
