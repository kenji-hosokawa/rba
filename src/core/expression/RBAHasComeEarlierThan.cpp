/**
 * 先行要求判定クラス定義ファイル
 */

#include "RBAHasComeEarlierThan.hpp"
#include "RBAContent.hpp"
#include "RBAArbitrator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

RBAModelElementType
RBAHasComeEarlierThan::getModelElementType() const
{
  return RBAModelElementType::HasComeEarlier;
}

void RBAHasComeEarlierThan::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

bool
RBAHasComeEarlierThan::executeCore(RBAConstraintInfo* info,
				       RBAArbitrator* arb) const
{
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(LOG_getSymbol());

  bool isResult {false};
  // 左辺のコンテントを取り出す
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* ruleObj {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  const RBAContent* contentLhs {nullptr};
  if(ruleObj != nullptr) {
    contentLhs = dynamic_cast<const RBAContent*>(ruleObj->getRawObject());
  }

  // 右辺のコンテントを取り出す
  RBAConstraintInfo* const rightInfo {info->getChild(1U)};
  ruleObj = getRhsOperand()->getReferenceObject(rightInfo, arb);
  const RBAContent* contentRhs {nullptr};
  if(ruleObj != nullptr) {
    contentRhs = dynamic_cast<const RBAContent*>(ruleObj->getRawObject());
  }

  if((contentLhs == nullptr) || (contentRhs == nullptr)) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    if (!((arb->getResult()->isActive(contentLhs))
        && (arb->getResult()->isActive(contentRhs)))) {
      info->setExceptionBeforeArbitrate(true);
    }
    else if(contentLhs == contentRhs) {
      isResult = false;
    }
    else {
      isResult = !arb->getResult()->isLater(contentLhs, contentRhs);
    }
  }
#ifdef RBA_USE_LOG
  std::string lhsName;
  std::string rhsName;
  std::string resultText;
  if(contentLhs == nullptr) {
    lhsName = "NULL";
  } else {
    lhsName = contentLhs->getElementName();
  }
  if (contentRhs == nullptr) {
    rhsName = "NULL";
  } else {
    rhsName = contentRhs->getElementName();
  }
  if (info->isExceptionBeforeArbitrate() == true ) {
    resultText = "is before arbitrate skip";
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
					RBAExecuteResult::SKIP);
  } else {
    resultText = RBALogManager::boolToString(isResult);
    if(isResult) {
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
					  RBAExecuteResult::TRUE);
    }
    else {
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
					  RBAExecuteResult::FALSE);
    }
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      Content[" + lhsName + "] has come earlier than Content[" + rhsName + "] " + resultText);
#endif
  // カバレッジ向けの制約階層構造から自分を削除
  LOG_removeHierarchy();
  return isResult;
}

#ifdef RBA_USE_LOG
const std::string
RBAHasComeEarlierThan::getSymbol() const
{
  return ".hasComeEarlierThan";
}

const std::string
RBAHasComeEarlierThan::getExpressionText() const
{
  RBAExpression* exprLhs = getLhsOperand();
  RBAExpression* exprRhs = getRhsOperand();
  return exprLhs->getExpressionText() + getSymbol()
    + "(" + exprRhs->getExpressionText() + ")";
}

const std::string
RBAHasComeEarlierThan::getCoverageExpressionText() const
{
  RBAExpression* exprLhs = getLhsOperand();
  RBAExpression* exprRhs = getRhsOperand();
  return exprLhs->getCoverageExpressionText() + getSymbol()
    + "(" + exprRhs->getCoverageExpressionText() + ")";
}

RBAExpressionType
RBAHasComeEarlierThan::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
