/// @file  RBARuleObjectMaker.cpp
/// @brief ルールオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBARuleObjectMaker.hpp"
#include "RBARuleObject.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBARuleObjectMaker::RBARuleObjectMaker(const std::string& label)
  : RBAModelElementMaker{label}
{  
}

RBAModelElement*
RBARuleObjectMaker::setProperty(RBAModelElement* element,
                                const RBAJsonElement* jsonElem,
                                RBAModelImpl* model,
                                RBAModelElement* owner)
{
  const auto ruleObj = dynamic_cast<RBARuleObject*>(element);

  // Tag
  const RBAJsonElement* const tags {jsonElem->findChildren("tags")};
  if (tags != nullptr) {
    for (const auto& tag : tags->getChildren()) {
      const RBAJsonElement* const tagName {tag->findChildren("name")};
      if (tagName != nullptr) {
        ruleObj->addTag(tagName->getString());
      }
    }
  }

  // owner
  const auto ownerRuleObj = dynamic_cast<RBARuleObject*>(owner);
  if (ownerRuleObj != nullptr) {
    ruleObj->setOwner(ownerRuleObj);
  }

  return ruleObj;
}

}
