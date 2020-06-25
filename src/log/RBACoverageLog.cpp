/**
 * カバレッジログクラス定義ファイル
 */

#include <algorithm>
#include <sstream>
#include "RBACoverageLog.hpp"

#include "RBAExpression.hpp"
#include "RBALog.hpp"
#include "RBAAbstractConstraint.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBAILogCollector.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

#ifdef RBA_USE_LOG
const std::string RBACoverageLog::SEP = ",";
const std::string RBACoverageLog::EXP_SEP = "\t";
const std::string RBACoverageLog::START = "START";
const std::string RBACoverageLog::END = "END";
const std::string RBACoverageLog::EXPRESSION = "EXPRESSION";
const std::string RBACoverageLog::CONSTRAINT = "Constraint";
const std::string RBACoverageLog::RULE = "Rule";

/**
 * 要求ログを1行で追加
 *
 * @param message
 */
void
RBACoverageLog::addRequestLogLine(const std::string& message)
{
  notify("#Request#" + message);
}

/**
 * アロケート設定ログを1行で追加
 *
 * @param message
 */
void
RBACoverageLog::addPrevResultLogLine(const std::string& message)
{
  notify("#PrevResult#" + message);
}

/**
 * 結果ログを1行で追加
 *
 * @param message
 */
void
RBACoverageLog::addResultLogLine(const std::string& message)
{
  notify("#Result#" + message);
}

void
RBACoverageLog::addStartLogLine(const std::string& log)
{
  notify(log);
}

void
RBACoverageLog::addCoverageLogCollector(RBAILogCollector* collector)
{
  collectors_.insert(collector);
}

void
RBACoverageLog::removeCoverageLogCollector(RBAILogCollector* collector)
{
  auto it = std::find(collectors_.begin(), collectors_.end(), collector);
  if(it != collectors_.end()) {
    collectors_.erase(it);
  }
}

/**
 * 制約ログを1行で追加
 *
 * @param message
 */
void
RBACoverageLog::addConstraintLogLine(const std::string& message)
{
  notify("#Constraint#" + message);
}

/**
 * 制約開始ログを追加
 *
 * @param constraint
 */
void
RBACoverageLog::addConstraintStartLog(const RBAAbstractConstraint* element)
{
  std::string isRuntime = "t";
  std::string eleName = element->getElementName();
  if(element->isConstraint()) {
    const RBAConstraintImpl* constraint
      = dynamic_cast<const RBAConstraintImpl*>(element);
    if(!constraint->isRuntime()) {
      isRuntime = "f";
    }
  }
  addConstraintLogLine(START + SEP + eleName + SEP + isRuntime);
}

/**
 * 制約終了ログを追加
 *
 * @param constraint
 */
void
RBACoverageLog::addConstraintEndLog(const RBAAbstractConstraint* element)
{
  addConstraintLogLine(END);
}

/**
 * 制約式実行ログを追加
 *
 * @param expressionText
 * @param result
 */
void
RBACoverageLog::addConstraintExpressionLog(
    const std::string& expressionText, RBAExecuteResult result)
{
  std::string resultMsg;
  if (RBAExecuteResult::TRUE == result) {
    resultMsg = "t";
  } else if (RBAExecuteResult::FALSE == result) {
    resultMsg = "f";
  } else if (RBAExecuteResult::EXE == result) {
    resultMsg = "e";
  } else if (RBAExecuteResult::NOTEXE == result) {
    resultMsg = "ne";
  } else {
    resultMsg = "skip";
  }
  addConstraintLogLine(
      EXPRESSION + EXP_SEP + getHierarchy() + EXP_SEP + expressionText + EXP_SEP
          + resultMsg);
}

/**
 * 制約式実行ログを追加（アクション用）
 *
 * @param expressionText
 */
void
RBACoverageLog::addConstraintExpressionLog(const std::string& expressionText)
{
  addConstraintLogLine(EXPRESSION + EXP_SEP +
		       getHierarchy() + EXP_SEP +
		       expressionText);
}

/**
 * 要求キャンセルログを1行で追加
 *
 * @param message
 */
void
RBACoverageLog::addCanceledRequestLogLine(const std::string& message)
{
  notify("#CanceledRequest#" + message);
}

/**
 * 制約構造ログを1行で追加
 *
 * @param message
 */
void
RBACoverageLog::addHierarchyOfConstraintLogLine(const std::string& message)
{
  notify("#HierarchyOfConstraint#" + message);
}

/**
 * 制約構造開始ログを1行で追加
 *
 * @param message
 */
void

RBACoverageLog::
addHierarchyOfConstraintStartLog(const RBAAbstractConstraint* element)
{
  std::string isRuntime = "t";
  std::string type = CONSTRAINT;
  std::string eleName = element->getElementName();
  if(element->isConstraint()) {
    const RBAConstraintImpl* constraint
      = dynamic_cast<const RBAConstraintImpl*>(element);
    if(!constraint->isRuntime()) {
      isRuntime = "f";
    }
  }
  else if(element->isRule()) {
    type = RULE;
  }
  addHierarchyOfConstraintLogLine(START + SEP +
                                  eleName + SEP +
                                  isRuntime + SEP + type);
}

/**
 * 制約構造終了ログを追加
 *
 * @param constraint
 */
void
RBACoverageLog::addHierarchyOfConstraintEndLog(const RBAAbstractConstraint* element)
{
  std::string eleName = element->getElementName();
  addHierarchyOfConstraintLogLine(END + SEP + eleName);
}

/**
 * 制約式実行ログを追加
 *
 * @param expressionText
 * @param result
 */
void
RBACoverageLog::
addHierarchyOfConstraintExpressionLog(const std::string& expressionText,
				      const RBAExpression* expression)
{
  addHierarchyOfConstraintLogLine(EXPRESSION + EXP_SEP +
				  getHierarchy() + EXP_SEP +
				  expressionText + EXP_SEP +
				  getExpressionType(expression));
}

// ---------------------------
// カバレッジ向けの制約ログの階層情報
// ---------------------------

/**
 * 制約の階層構造を初期化する
 */
void
RBACoverageLog::initConstraintHierarchy()
{
  hierarchys_.clear();
}

/**
 * 制約の階層構造を文字列で返す
 *
 * @return
 */
std::string
RBACoverageLog::getHierarchy() const
{
  std::ostringstream oss;

  std::string pre;
  int32_t i=0;
  for(std::string now : hierarchys_) {
    if((i != 0) && (pre[0] != '#')) {
      // 初回でかつ複数演算子扱いでなければ分割識別子を追加
      oss << "#";
    }
    pre = now;
    if(now[0] == '#') {
      now = now.substr(1, now.length());
    }
    oss << now;
    i++;
  }

  return oss.str();
}

/**
 * 制約の階層構造を追加する
 *
 * @param data
 * @return
 */
bool
RBACoverageLog::addHierarchy(const std::string& data)
{
  hierarchys_.push_back(data);
  return true;
}

/**
 * 制約の階層構造を削除する
 *
 * @param data
 * @return
 */
void
RBACoverageLog::removeHierarchy()
{
  hierarchys_.pop_back();
}

/**
 * 階層構造ログに出力する式の型文字列を返す
 *
 * @param expression
 * @return
 */
std::string
RBACoverageLog::getExpressionType(const RBAExpression* expression) const
{
  switch(expression->getUnderlyingType()) {
  case RBAExpressionType::BOOLEAN:
    return "boolean";
  case RBAExpressionType::ACTION:
  case RBAExpressionType::SET_OF_ACTION:
    return "action";
  default:
    return "unknown";
  }
}

void
RBACoverageLog::notify(const std::string& log)
{
  for(RBAILogCollector* collector : collectors_) {
    collector->log(log);
  }
}
#endif

}
