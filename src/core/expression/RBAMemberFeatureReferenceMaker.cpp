/// @file  RBAMemberFeatureReferenceMaker.cpp
/// @brief プロパティのObjectReferenceオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAMemberFeatureReferenceMaker.hpp"
#include "RBAObjectReference.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAAbstractProperty.hpp"

namespace rba
{

RBAMemberFeatureReferenceMaker::RBAMemberFeatureReferenceMaker()
  : RBAObjectReferenceMaker{"MemberFeatureReference"}
{
}

std::unique_ptr<RBAModelElement>
RBAMemberFeatureReferenceMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAObjectReference>();
}

RBAModelElement*
RBAMemberFeatureReferenceMaker::setProperty(RBAModelElement* element,
                                            const RBAJsonElement* jsonElem,
                                            RBAModelImpl* model,
                                            RBAModelElement* owner)
{
  RBAObjectReference* const objRef {dynamic_cast<RBAObjectReference*>(element)};

  // Set reference object
  objRef->setRefObject(getRuleObject(jsonElem,model));

  return objRef;
}

const RBARuleObject*
RBAMemberFeatureReferenceMaker::getRuleObject(const RBAJsonElement* const jsonElem,
                                              RBAModelImpl* const model)
{
  const RBARuleObject* refObj {nullptr};
  const auto typeStr = jsonElem->findChildren("type")->getString();
  const auto refObjStr = jsonElem->findChildren("refObject")->getString();

  if (jsonElem->findChildren("class")->getString() == "ObjectReference") {
    refObj = dynamic_cast<RBARuleObject*>(getMaker(typeStr)->getInstance(model, refObjStr));
  } else {  // jsonElem->findChildren("class")->getString() == "MemberFeatureReference"
    // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
    // 【ルールに逸脱している内容】
    // getRuleObject()を再帰呼び出ししている
    // 【ルールを逸脱しても問題ないことの説明】
    // 制約式に、「コンテント名.ステートマシン名.状態名」をしようしたとき、
    // CONTENTのMemberのSTATEMACHINEのMemberのSTATEMACHINE_STATEとなるので、再帰呼び出しを使用している
    // ルールモデルの要素数は有限であり、循環関係にないため、スタックオーバーフローすることはなく、問題無い
    const auto owner = const_cast<RBARuleObject*>(getRuleObject(jsonElem->findChildren("operand")->getChild(), model));
    refObj = owner->getMember(refObjStr);
    if (refObj == nullptr) {
      if (getMaker(typeStr) != nullptr) {
        refObj = dynamic_cast<RBARuleObject*>(getMaker(typeStr)->getInstance(model, refObjStr, owner));
      }
      if ((refObj == nullptr)
          && (jsonElem->findChildren("type")->getString() == "PROPERTY")) {
        refObj = dynamic_cast<RBASceneImpl*>(owner)->addProperty(refObjStr, -99);
      }
    }
  }
  return refObj;
}
}
