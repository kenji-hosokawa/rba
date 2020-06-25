/// @file  RBAContentStateMaker.hpp
/// @brief ContentStateオブジェクト生成抽象クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBACONTENTSTATEMAKER_HPP
#define RBACONTENTSTATEMAKER_HPP

#include "RBARuleObjectMaker.hpp"

namespace rba
{

/// @brief ContentStateオブジェクト生成クラス
class RBAContentStateMaker : public RBARuleObjectMaker
{
public:
  explicit RBAContentStateMaker(const std::string& label);
  RBAContentStateMaker(const RBAContentStateMaker&)=delete;
  RBAContentStateMaker(const RBAContentStateMaker&&)=delete;
  RBAContentStateMaker& operator=(const RBAContentStateMaker&)=delete;
  RBAContentStateMaker& operator=(const RBAContentStateMaker&&)=delete;
  virtual ~RBAContentStateMaker()=default;

public:

  RBAModelElement* getInstance(RBAModelImpl* model,
                               const std::string& name="",
                               RBAModelElement* owner=nullptr) override;

protected:
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
