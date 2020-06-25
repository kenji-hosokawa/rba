/// @file  RBAExpreessionMaker.cpp
/// @brief 式オブジェクト生成の抽象クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAExpressionMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBALetStatementMaker.hpp"
#include "RBALetStatement.hpp"

namespace rba
{

RBAExpressionMaker::RBAExpressionMaker(const std::string& label)
  : RBAModelElementMaker{label}
{
}

std::int32_t
RBAExpressionMaker::setLetStatement(RBAModelImpl* const model,
                                    RBAExpression* const expr,
                                    const RBAJsonElement* const jsonElem)
{
  std::int32_t var_num {0};
  const RBAJsonElement* const letElem {jsonElem->findChildren("letStatements")};
  if(letElem != nullptr) {
    RBALetStatementMaker letMaker;
    letMaker.setFactory(getFactory());
    for(const auto& param : letElem->getChildren()) {  
      // letMaker::create()でpushVariable()を実施
      RBALetStatement* const letExpr
        {dynamic_cast<RBALetStatement*>(letMaker.create(param.get(), model))};
      expr->addLetStatement(letExpr);
      var_num += 1;
    }
  }

  return var_num;
}

}
