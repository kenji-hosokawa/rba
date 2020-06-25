/**
 * 抽象探索クラスヘッダファイル
 */

#ifndef RBAABSTRACTCOLLECTOR_HPP
#define RBAABSTRACTCOLLECTOR_HPP

#include <set>

#include "RBAExpressionVisitor.hpp"
#include "RBAExpression.hpp"

namespace rba
{
class RBAModelImpl;
class RBARuleObject;

class RBAAbstractCollector : public RBAExpressionVisitor
{
 public:
  RBAAbstractCollector(RBAModelImpl* const model);
  RBAAbstractCollector(const RBAAbstractCollector&)=default;
  RBAAbstractCollector(RBAAbstractCollector&&)=default;
  RBAAbstractCollector& operator=(const RBAAbstractCollector&)=default;
  RBAAbstractCollector& operator=(RBAAbstractCollector&&)=default;
  virtual ~RBAAbstractCollector()=default;

  // エリアの状態参照
  void visit(RBAIsDisplayed& exp) override;
  void visit(RBADisplayingContent& exp) override;
  void visit(RBAAllocatedContent& exp) override;
  void visit(RBAIsHidden& exp) override;
  void visit(RBAContentValue& exp) override;
  void visit(RBAGetContentsList& exp) override;
  void visit(RBAActiveContents& exp) override;

  // 表示コンテントの状態参照
  void visit(RBAIsActive& exp) override;
  void visit(RBAIsVisible& exp) override;
  void visit(RBAStateValue& exp) override;
  void visit(RBAHasBeenDisplayed& exp) override;
  void visit(RBAHasComeEarlierThan& exp) override;
  void visit(RBAHasComeLaterThan& exp) override;
  void visit(RBAGetAllocatables& exp) override;
  void visit(RBAActiveState& exp) override;

  // ゾーンの状態参照
  void visit(RBAIsOutputted& exp) override;
  void visit(RBAOutputtingSound& exp) override;
  // allocatedContentはエリアと共通
  void visit(RBAIsMuted& exp) override;
  void visit(RBAIsAttenuated& exp) override;
  // contentValueはエリアと共通
  // contentsListはエリアと共通

  // 音声コンテントの状態参照
  // isActiveは表示コンテントと共通
  void visit(RBAIsSounding& exp) override;
  // stateValueは表示コンテントと共通
  // hasComeEarlierThanは表示コンテントと共通
  // hasComeLaterThanは表示コンテントと共通
  // allocatablesは表示コンテントと共通
  // activeStateは表示コンテントと共通

  // シーン参照
  void visit(RBAIsOn& exp) override;
  void visit(RBAGetProperty& exp) override;

  void visit(RBAIsTypeOfOperator& exp) override;

  // 演算子
  void visit(RBAAndOperator& exp) override;
  void visit(RBAOrOperator& exp) override;
  void visit(RBANotOperator& exp) override;
  void visit(RBAImpliesOperator& exp) override;
  void visit(RBAIsEqualToOperator& exp) override;
  void visit(RBAObjectCompare& exp) override;
  void visit(RBAIsGreaterThanOperator& exp) override;
  void visit(RBAIsGreaterThanEqualOperator& exp) override;
  void visit(RBAIsLowerThanOperator& exp) override;
  void visit(RBAIsLowerThanEqualOperator& exp) override;

  // 量化記号
  void visit(RBAForAllOperator& exp) override;
  void visit(RBAExistsOperator& exp) override;

  // 組込み定義式
  void visit(RBAAllInstanceOfArea& exp) override;
  void visit(RBAAllInstanceOfViewContent& exp) override;
  void visit(RBAAllInstanceOfZone& exp) override;
  void visit(RBAAllInstanceOfSoundContent& exp) override;

  // 構文
  void visit(RBAIfStatement& exp) override;
  void visit(RBALetStatement& exp) override;

  // 修飾子
  void visit(RBAPreviousModifier& exp) override;

  // 集合操作
  void visit(RBAMaxOperator& exp) override;
  void visit(RBAMinOperator& exp) override;
  void visit(RBASelectOperator& exp) override;
  void visit(RBASizeOperator& exp) override;

  // オブジェクトリファレンス
  void visit(RBAObjectReference& exp) override;
  void visit(RBASetOfOperator& exp) override;

 protected:
  void visitLetStatement(RBAExpression& exp) ;

  // ゲッタ、セッタ
  std::set<const RBARuleObject*>& getLetVal();
  void addLetVal(const RBARuleObject* const obj);
  bool isVisitsLetStatement() const;
  bool isLhs() const;
  void setLhs(const bool lhs);
  bool isPositive() const;
  RBAModelImpl* getModel() const;
  bool isPreviousModifier() const;

 private:
  // letStatementの評価結果としてとり得るオブジェクト
  std::set<const RBARuleObject*> letVal_;
  // getReferenceObject()内で参照するモデル
  RBAModelImpl* model_;
  // 左辺を探索中のとき、true
  // 上記以外の時、false
  bool isLhs_;
  // (pre)の下にあるExpressionにいるとき、true
  // 上記以外の時、false
  bool isPreviousModifier_;
  // Notで反転していないとき、true
  // Notで反転しているとき、false
  bool isPositive_;
  // letStatementの中を探索中のとき、true
  // 上記以外の時、false
  bool visitsLetStatement_;
};

} /* namespace rba */

#endif /* RBAABSTRACTCOLLECTOR_HPP */
