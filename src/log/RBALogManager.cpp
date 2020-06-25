/**
 * ログマネージャクラス定義ファイル
 */

#include <sstream>
#include <bitset>
#include "RBALogManager.hpp"
#include "RBALog.hpp"

namespace rba
{

#ifdef RBA_USE_LOG
RBALogManager* RBALogManager::instance_=nullptr;

const std::string RBALogManager::STR_TRUE = "true";
const std::string RBALogManager::STR_FALSE = "false";
std::string RBALogManager::indent_ = "";

RBALogManager::RBALogManager()
{
}

//
// Static method
//

void
RBALogManager::setLogManager(RBALogManager* logManager)
{
  instance_ = logManager;
}

RBALogManager*
RBALogManager::getLogManager()
{
  return instance_;
}

void
RBALogManager::setType(std::uint16_t logType)
{
  if(instance_) {
    instance_->setTypeImpl(logType);
  }
}

void
RBALogManager::setEnable(std::uint16_t logType, bool sw)
{
  if(instance_) {
    instance_->setEnableImpl(logType, sw);
  }
}  

void
RBALogManager::init(int32_t level)
{
  if(instance_) {
    instance_->initImpl(level);
  }
}

void
RBALogManager::requestLogLine(const std::string& message)
{
  if(instance_) {
    instance_->requestLogLineImpl(message);
  }
}

void
RBALogManager::resultLogLine(const std::string& message)
{
  if(instance_) {
    instance_->resultLogLineImpl(message);
  }
}

void
RBALogManager::arbitrateAreaLogLine(const std::string& message)
{
  if(instance_) {
    instance_->arbitrateAreaLogLineImpl(message);
  }
}

void
RBALogManager::arbitrateContentLogLine(const std::string& message)
{
  if(instance_) {
    instance_->arbitrateContentLogLineImpl(message);
  }
}

void
RBALogManager::arbitrateConstraintLogLine(const std::string& message)
{
  if(instance_) {
    instance_->arbitrateConstraintLogLineImpl(message);
  }
}

void
RBALogManager::arbitrateConstraintLogicLogLine(const std::string& message)
{
  if(instance_) {
    instance_->arbitrateConstraintLogicLogLineImpl(message);
  }
}

void
RBALogManager::allConstraintLogLine(const std::string& message)
{
  if(instance_) {
    instance_->allConstraintLogLineImpl(message);
  }
}

void
RBALogManager::cancelRequestLogLine(const std::string& message)
{
  if(instance_) {
    instance_->cancelRequestLogLineImpl(message);
  }
}

std::string
RBALogManager::getArbitrateLog()
{
  if(instance_) {
    return instance_->getArbitrateLogImpl();
  }
  else {
    return "";
  }
}

std::string
RBALogManager::getAllConstraintLog()
{
  if(instance_) {
    return instance_->getAllConstraintLogImpl();
  }
  else {
    return "";
  }
}

std::string
RBALogManager::getCheckAllConstraintLog()
{
  if(instance_) {
    return instance_->getCheckAllConstraintLogImpl();
  }
  else {
    return "";
  }
}

std::string
RBALogManager::getRequestLog()
{
  if(instance_) {
    return instance_->getRequestLogImpl();
  }
  else {
    return "";
  }
}

std::string
RBALogManager::getPreviousResultLog()
{
  if(instance_) {
    return instance_->getPreviousResultLogImpl();
  }
  else {
    return "";
  }
}

std::string
RBALogManager::getResultLog()
{
  if(instance_) {
    return instance_->getResultLogImpl();
  }
  else {
    return "";
  }
}

std::string
RBALogManager::getCancelRequestLog()
{
  if(instance_) {
    return instance_->getCancelRequestLogImpl();
  }
  else {
    return "";
  }
}

void
RBALogManager::coverageRequestLogLine(const std::string& message)
{
  if(instance_) {
    instance_->coverageRequestLogLineImpl(message);
  }
}

void
RBALogManager::coveragePrevResultLogLine(const std::string& message)
{
  if(instance_) {
    instance_->coveragePrevResultLogLineImpl(message);
  }
}

void
RBALogManager::coverageResultLogLine(const std::string& message)
{
  if(instance_) {
    instance_->coverageResultLogLineImpl(message);
  }
}

void
RBALogManager::coverageConstraintStartLog(const RBAAbstractConstraint* constraint)
{
  if(instance_) {
    instance_->coverageConstraintStartLogImpl(constraint);
  }
}

void
RBALogManager::coverageConstraintEndLog(const RBAAbstractConstraint* constraint)
{
  if(instance_) {
    instance_->coverageConstraintEndLogImpl(constraint);
  }
}

void
RBALogManager::coverageConstraintExpressionLog(
    const std::string& expressionText, RBAExecuteResult result) {
  if (instance_) {
    instance_->coverageConstraintExpressionLogImpl(expressionText, result);
  }
}

void
RBALogManager::
coverageConstraintExpressionLog(const std::string& expressionText)
{
  if(instance_) {
    instance_->coverageConstraintExpressionLogImpl(expressionText);
  }
}

void
RBALogManager::coverageCanceledRequestLogLine(const std::string& message)
{
  if(instance_) {
    instance_->coverageCanceledRequestLogLineImpl(message);
  }
}

void
RBALogManager::addStartLogLine(const std::string& log)
{
  if(instance_) {
    instance_->addStartLogLineImpl(log);
  }
}

void
RBALogManager::addCoverageLogCollector(RBAILogCollector* collector)
{
  coverageLog_.addCoverageLogCollector(collector);
}

void
RBALogManager::removeCoverageLogCollector(RBAILogCollector* collector)
{
  coverageLog_.removeCoverageLogCollector(collector);
}

void
RBALogManager::coverageHierarchyOfConstraintLogLine(const std::string& message)
{
  if(instance_) {
    instance_->coverageHierarchyOfConstraintLogLineImpl(message);
  }
}

void
RBALogManager::
coverageHierarchyOfConstraintStartLog(const RBAAbstractConstraint* constraint)
{
  if(instance_) {
    instance_->coverageHierarchyOfConstraintStartLogImpl(constraint);
  }
}

void
RBALogManager::
coverageHierarchyOfConstraintEndLog(const RBAAbstractConstraint* constraint)
{
  if(instance_) {
    instance_->coverageHierarchyOfConstraintEndLogImpl(constraint);
  }
}

void
RBALogManager::
coverageHierarchyOfConstraintExpressionLog(const std::string& expressionText,
					   RBAExpression* expression)
{
  if(instance_) {
    instance_->coverageHierarchyOfConstraintExpressionLogImpl(expressionText,
							      expression);

  }
}

void
RBALogManager::initConstraintHierarchy()
{
  if(instance_) {
    instance_->initConstraintHierarchyImpl();
  }
}

bool RBALogManager::addHierarchy(const std::string& data)
{
{
  if(instance_) {
    return instance_->addHierarchyImpl(data);
  }
  else {
    return true;
  }
}
}

void RBALogManager::removeHierarchy()
{
  if(instance_) {
    instance_->removeHierarchyImpl();
  }
}

//
// Private method
//

void
RBALogManager::setTypeImpl(std::uint16_t logType)
{
  execType_ = logType;
}

void
RBALogManager::setEnableImpl(std::uint16_t logType, bool sw)
{
  if(sw) {
    requestType_ |= logType;
  } else {
    requestType_ &= ~logType;
  }
}

/**
 * ログを初期化する
 */
void
RBALogManager::initImpl(int32_t level)
{
  level_ = level;
  requestLogs_.clear();
  previousResultLogs_.clear();
  resultLogs_.clear();
  cancelLogs_.clear();
  checkAllConstraintsLogs_.clear();
  allConstraintLogs_.clear();
  arbitrateLogs_.clear();
}

/**
 * 要求情報を1行でログする
 * @param message
 */
void
RBALogManager::requestLogLineImpl(const std::string& message)
{
  if((TYPE_REQUEST & requestType_) != 0U) {
    requestLogs_.push_back(std::make_shared<RBALog>(1, indent_ + message));
  }
}

/**
 * 結果情報を1行でログする
 * @param message
 */
void
RBALogManager::resultLogLineImpl(const std::string& message)
{
  if((TYPE_RESULT & requestType_ & execType_) != 0U) {
    resultLogs_.push_back(std::make_shared<RBALog>(1, indent_ + message));
  }
  if((TYPE_PREVIOUS_RESULT & requestType_ & execType_) != 0U) {
    previousResultLogs_.push_back(std::make_shared<RBALog>(1, indent_ + message));
  }
}

/**
 * エリア調停情報を1行でログする
 * @param message
 */
void
RBALogManager::arbitrateAreaLogLineImpl(const std::string& message)
{
  if((TYPE_ARBITRATE & requestType_) != 0U) {
    arbitrateLogs_.push_back(std::make_shared<RBALog>(2, indent_ + message));
  }
}

/**
 * コンテンツ調停情報を1行でログする
 * @param message
 */
void
RBALogManager::arbitrateContentLogLineImpl(const std::string& message)
{
  if((TYPE_ARBITRATE & requestType_) != 0U) {
    arbitrateLogs_.push_back(std::make_shared<RBALog>(2, indent_ + message));
  }
}

/**
 * 制約確認情報を1行でログする
 * @param message
 */
void
RBALogManager::arbitrateConstraintLogLineImpl(const std::string& message)
{
  if((TYPE_ARBITRATE & requestType_ & execType_) != 0U) {
    arbitrateLogs_.push_back(std::make_shared<RBALog>(3, indent_ + message));
  }
  if((TYPE_CHECK_ALL_CONSTRAINTS & requestType_ & execType_) != 0U) {
    checkAllConstraintsLogs_.push_back(std::make_shared<RBALog>(3, indent_ + message));
  }
  if((TYPE_CANCEL_REQUEST & requestType_ & execType_) != 0U) {
    cancelLogs_.push_back(std::make_shared<RBALog>(3, indent_ + message));
  }
}

/**
 * 制約ロジック情報を1行でログする
 * @param message
 */
void
RBALogManager::arbitrateConstraintLogicLogLineImpl(const std::string& message)
{
  if((TYPE_ARBITRATE & requestType_ & execType_) != 0U) {
    arbitrateLogs_.push_back(std::make_shared<RBALog>(4, indent_ + message));
  }
  if((TYPE_CHECK_ALL_CONSTRAINTS & requestType_ & execType_) != 0U) {
    checkAllConstraintsLogs_.push_back(std::make_shared<RBALog>(4, indent_ + message));
  }
  if((TYPE_CANCEL_REQUEST & requestType_ & execType_) != 0U) {
    cancelLogs_.push_back(std::make_shared<RBALog>(4, indent_ + message));
  }
}

/**
 * 全制約チェックログを1行で追加する
 * @param message
 */
void
RBALogManager::allConstraintLogLineImpl(const std::string& message)
{
  if((TYPE_ALL_CONSTRAINTS & requestType_) != 0U) {
    allConstraintLogs_.push_back(std::make_shared<RBALog>(0, indent_ + message));
  }
}

/**
 * 全制約チェックログを1行で追加する
 * @param message
 */
void
RBALogManager::cancelRequestLogLineImpl(const std::string& message)
{
  if((TYPE_CANCEL_REQUEST & requestType_) != 0U) {
    cancelLogs_.push_back(std::make_shared<RBALog>(2, indent_ + message));
  }
}

/**
 * 設定レベル以下の調停ログの文字列を取得する
 * @return
 */
std::string
RBALogManager::getArbitrateLogImpl()
{
  std::ostringstream oss;
  for(auto it=arbitrateLogs_.begin(); it!=arbitrateLogs_.end(); it++) {
    if(it->get()->getLevel() <= level_) {
      oss << it->get()->getLog() << std::endl;
    }
  }

  return oss.str();
}

/**
 * get all constraints log
 * @return
 */
std::string
RBALogManager::getAllConstraintLogImpl()
{
  std::ostringstream oss;
  for(auto it=allConstraintLogs_.begin(); it!=allConstraintLogs_.end(); it++) {
    RBALog* log = it->get();
    if(log->getLevel() <= level_) {
      oss << log->getLog() << std::endl;
    }
  }

  return oss.str();
}

/**
 * get check all constraints log
 * @return
 */
std::string
RBALogManager::getCheckAllConstraintLogImpl()
{
  std::ostringstream oss;
  for(auto it=checkAllConstraintsLogs_.begin();
      it!=checkAllConstraintsLogs_.end(); it++) {
    RBALog* log = it->get();
    if(log->getLevel() <= level_) {
      oss << log->getLog() << std::endl;
    }
  }

  return oss.str();
}

/**
 * get request log
 * @return
 */
std::string
RBALogManager::getRequestLogImpl()
{
  std::ostringstream oss;
  for(auto it=requestLogs_.begin(); it!=requestLogs_.end(); it++) {
    RBALog* log = it->get();
    if(log->getLevel() <= level_) {
      oss << log->getLog() << std::endl;
    }
  }

  return oss.str();
}

/**
 * get previous result log
 * @return
 */
std::string
RBALogManager::getPreviousResultLogImpl()
{
  std::ostringstream oss;
  for(auto it=previousResultLogs_.begin();
      it!=previousResultLogs_.end(); it++) {
    RBALog* log = it->get();
    if(log->getLevel() <= level_) {
      oss << log->getLog() << std::endl;
    }
  }

  return oss.str();
}

/**
 * get result log
 * @return
 */
std::string
RBALogManager::getResultLogImpl()
{
  std::ostringstream oss;
  for(auto it=resultLogs_.begin(); it!=resultLogs_.end(); it++) {
    RBALog* log = it->get();
    if(log->getLevel() <= level_) {
      oss << log->getLog() << std::endl;
    }
  }

  return oss.str();
}

/**
 * get rule log
 * @return
 */
std::string
RBALogManager::getCancelRequestLogImpl()
{
  std::ostringstream oss;
  for(auto it=cancelLogs_.begin(); it!=cancelLogs_.end(); it++) {
    RBALog* log = it->get();
    if(log->getLevel() <= level_) {
      oss << log->getLog() << std::endl;
    }
  }

  return oss.str();
}

// -------------------
// カバレッジ向けのログ情報
// -------------------
/**
 * カバレッジ向けの要求ログを1行で追加する
 * @param message
 */
void
RBALogManager::coverageRequestLogLineImpl(const std::string& message)
{
  coverageLog_.addRequestLogLine(message);
}

/**
 * カバレッジ向けのアロケート設定ログを1行で追加する
 * @param message
 */
void
RBALogManager::coveragePrevResultLogLineImpl(const std::string& message)
{
  coverageLog_.addPrevResultLogLine(message);
}

/**
 * カバレッジ向けの結果ログを1行で追加する
 * @param message
 */
void
RBALogManager::coverageResultLogLineImpl(const std::string& message)
{
  coverageLog_.addResultLogLine(message);
}

/**
 * カバレッジ向けの制約開始ログを追加する
 * @param constraint
 */
void
RBALogManager::coverageConstraintStartLogImpl(const RBAAbstractConstraint* constraint)
{
  if ((execType_ == TYPE_ARBITRATE) ||
      (execType_ == TYPE_CANCEL_REQUEST) ||
      (execType_ == TYPE_NOTHING)) {
    coverageLog_.addConstraintStartLog(constraint);
  }
}

/**
 * カバレッジ向けの制約終了ログを追加する
 * @param constraint
 */
void
RBALogManager::coverageConstraintEndLogImpl(const RBAAbstractConstraint* constraint)
{
  if ((execType_ == TYPE_ARBITRATE) ||
      (execType_ == TYPE_CANCEL_REQUEST) ||
      (execType_ == TYPE_NOTHING)) {
    coverageLog_.addConstraintEndLog(constraint);
  }
}

/**
 * カバレッジ向けの制約実行ログを追加する
 * @param expressionText
 * @param result
 */
void
RBALogManager::coverageConstraintExpressionLogImpl(
    const std::string& expressionText, RBAExecuteResult result)
{
  if ((execType_ == TYPE_ARBITRATE) ||
      (execType_ == TYPE_CANCEL_REQUEST) ||
      (execType_ == TYPE_NOTHING)) {
    coverageLog_.addConstraintExpressionLog(expressionText, result);
  }
}

/**
 * カバレッジ向けのアクション用制約実行ログを追加する
 * @param expressionText
 */
void
RBALogManager::
coverageConstraintExpressionLogImpl(const std::string& expressionText)
{
  coverageLog_.addConstraintExpressionLog(expressionText);
}

/**
 * カバレッジ向けの要求キャンセルログを1行で追加する
 * @param message
 */
void
RBALogManager::coverageCanceledRequestLogLineImpl(const std::string& message)
{
  coverageLog_.addCanceledRequestLogLine(message);
}

/**
 * add start log line
 * @param log
 */
void
RBALogManager::addStartLogLineImpl(const std::string& log)
{
  coverageLog_.addStartLogLine(log);
}

/**
 * カバレッジ向けの制約構造ログを1行で追加する
 * @param message
 */
void
RBALogManager::coverageHierarchyOfConstraintLogLineImpl(const std::string& message)
{
  coverageLog_.addHierarchyOfConstraintLogLine(message);
}

/**
 * カバレッジ向けの制約構造開始ログを追加する
 * @param constraint
 */
void
RBALogManager::
coverageHierarchyOfConstraintStartLogImpl(const RBAAbstractConstraint* constraint)
{
  coverageLog_.addHierarchyOfConstraintStartLog(constraint);
}

/**
 * カバレッジ向けの制約構造終了ログを追加する
 * @param constraint
 */
void
RBALogManager::
coverageHierarchyOfConstraintEndLogImpl(const RBAAbstractConstraint* constraint)
{
  coverageLog_.addHierarchyOfConstraintEndLog(constraint);
}

/**
 * カバレッジ向けの制約構造式ログを追加する
 * @param expressionText
 * @param expression
 */
void
RBALogManager::
coverageHierarchyOfConstraintExpressionLogImpl(const std::string& expressionText,
					       const RBAExpression* expression)
{
  coverageLog_.addHierarchyOfConstraintExpressionLog(expressionText,
						     expression);
}

// ---------------------------
// カバレッジ向けの制約ログの階層情報
// ---------------------------
/**
 * 制約の階層構造を初期化する
 */
void
RBALogManager::initConstraintHierarchyImpl()
{
  coverageLog_.initConstraintHierarchy();
}

/**
 * 制約の階層構造を追加する
 * @param data
 * @return
 */
bool
RBALogManager::addHierarchyImpl(const std::string& data)
{
  if ((execType_ == TYPE_ARBITRATE) ||
      (execType_ == TYPE_CANCEL_REQUEST) ||
      (execType_ == TYPE_NOTHING)) {
    return coverageLog_.addHierarchy(data);
  } else {
    return false;
  }
}

/**
 * 制約の階層構造を削除する
 * @param data
 * @return
 */
void
RBALogManager::removeHierarchyImpl()
{
  if ((execType_ == TYPE_ARBITRATE) ||
      (execType_ == TYPE_CANCEL_REQUEST) ||
      (execType_ == TYPE_NOTHING)) {
    coverageLog_.removeHierarchy();
  }
}

const std::string&
RBALogManager::boolToString(const bool value)
{
  if (value == true) {
    return STR_TRUE;
  } else {
    return STR_FALSE;
  }
}

void
RBALogManager::setIndent(std::int32_t nest)
{
  indent_ = "";
  for (std::int32_t i = 0; i < nest; ++i) {
    indent_ += "    ";
  }
}
#endif

}
