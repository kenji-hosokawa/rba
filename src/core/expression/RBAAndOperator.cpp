/**
 * ANDオペレータクラス定義ファイル
 */

#include "RBAAndOperator.hpp"

#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAAndOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAAndOperator::getModelElementType() const
{
  return RBAModelElementType::AndOperator;
}

bool
RBAAndOperator::executeCore(RBAConstraintInfo* info,
                            RBAArbitrator * arb) const
{
  // カバレッジ向けの制約階層構造に自分を追加
  LOG_addHierarchy(LOG_getSymbol());
  
  std::uint32_t falseCount {0U};
  std::uint32_t exceptionCount {0U};
  std::uint32_t index {0U};
  for(const auto& ope : getOperand()) {
    // カバレッジ向けの制約階層構造に回数を追加
    LOG_addHierarchy("#" + std::to_string(index));

    RBAConstraintInfo* const childInfo {info->getChild(index)};
    const bool res {ope->execute(childInfo, arb)};
    if(childInfo->isExceptionBeforeArbitrate()) {
      exceptionCount++;
    } else if(!res) {
      falseCount++;
    } else {
      ;
    }

    // カバレッジ向けの制約階層構造から回数を削除
    LOG_removeHierarchy();
    index++;
  }

  // 失敗あり
  if (falseCount > 0U) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] false");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
    // カバレッジ向けの制約階層構造から自分を削除
    LOG_removeHierarchy();
    return false;
  }

  // 例外
  if (exceptionCount > 0U) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
    // カバレッジ向けの制約階層構造から自分を削除
    LOG_removeHierarchy();
    info->setExceptionBeforeArbitrate(true);
    return false;
  }

  LOG_arbitrateConstraintLogicLogLine(
      "      [" + LOG_getExpressionText() + "] true");
  LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                      RBAExecuteResult::TRUE);
  // カバレッジ向けの制約階層構造から自分を削除
  LOG_removeHierarchy();

  return true;
}

#ifdef RBA_USE_LOG
const std::string
RBAAndOperator::getSymbol() const
{
  return "AND";
}
#endif

}
