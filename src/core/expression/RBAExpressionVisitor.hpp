/**
 * Expressionビジタークラスヘッダファイル
 */

#ifndef RBAEXPRESSIONVISITOR_HPP
#define RBAEXPRESSIONVISITOR_HPP

namespace rba {
class RBAIsDisplayed;
class RBADisplayingContent;
class RBAAllocatedContent;
class RBAIsHidden;
class RBAContentValue;
class RBAGetContentsList;
class RBAIsActive;
class RBAIsVisible;
class RBAStateValue;
class RBAHasBeenDisplayed;
class RBAHasComeEarlierThan;
class RBAHasComeLaterThan;
class RBAGetAllocatables;
class RBAIsOutputted;
class RBAOutputtingSound;
class RBAIsMuted;
class RBAIsAttenuated;
class RBAIsSounding;
class RBAIsOn;
class RBAGetProperty;
class RBAAndOperator;
class RBAOrOperator;
class RBANotOperator;
class RBAImpliesOperator;
class RBAIsEqualToOperator;
class RBAObjectCompare;
class RBAIsGreaterThanOperator;
class RBAIsGreaterThanEqualOperator;
class RBAIsLowerThanOperator;
class RBAIsLowerThanEqualOperator;
class RBAForAllOperator;
class RBAExistsOperator;
class RBAAllInstanceOfArea;
class RBAAllInstanceOfViewContent;
class RBAAllInstanceOfZone;
class RBAAllInstanceOfSoundContent;
class RBAIfStatement;
class RBALetStatement;
class RBAPreviousModifier;
class RBAActiveState;
class RBAActiveContents;
class RBAMaxOperator;
class RBAMinOperator;
class RBASelectOperator;
class RBASizeOperator;
class RBAObjectReference;
class RBASetOfOperator;
class RBAIsTypeOfOperator;

class RBAExpressionVisitor {
 public:
  RBAExpressionVisitor()=default;
  RBAExpressionVisitor(const RBAExpressionVisitor&)=delete;
  RBAExpressionVisitor(const RBAExpressionVisitor&&)=delete;
  RBAExpressionVisitor& operator=(const RBAExpressionVisitor&)=delete;
  RBAExpressionVisitor& operator=(const RBAExpressionVisitor&&)=delete;
  virtual ~RBAExpressionVisitor() = default;

  // エリアの状態参照
  virtual void visit(RBAIsDisplayed& exp) = 0;
  virtual void visit(RBADisplayingContent& exp) = 0;
  virtual void visit(RBAAllocatedContent& exp) = 0;
  virtual void visit(RBAIsHidden& exp) = 0;
  virtual void visit(RBAContentValue& exp) = 0;
  virtual void visit(RBAGetContentsList& exp) = 0;
  virtual void visit(RBAActiveContents& exp) = 0;

  // 表示コンテントの状態参照
  virtual void visit(RBAIsActive& exp) = 0;
  virtual void visit(RBAIsVisible& exp) = 0;
  virtual void visit(RBAStateValue& exp) = 0;
  virtual void visit(RBAHasBeenDisplayed& exp) = 0;
  virtual void visit(RBAHasComeEarlierThan& exp) = 0;
  virtual void visit(RBAHasComeLaterThan& exp) = 0;
  virtual void visit(RBAGetAllocatables& exp) = 0;
  virtual void visit(RBAActiveState& exp) = 0;

  // ゾーンの状態参照
  virtual void visit(RBAIsOutputted& exp) = 0;
  virtual void visit(RBAOutputtingSound& exp) = 0;
  // allocatedContentはエリアと共通
  virtual void visit(RBAIsMuted& exp) = 0;
  virtual void visit(RBAIsAttenuated& exp) = 0;
  // contentValueはエリアと共通
  // contentsListはエリアと共通

  // 音声コンテントの状態参照
  // isActiveは表示コンテントと共通
  virtual void visit(RBAIsSounding& exp) = 0;
  // stateValueは表示コンテントと共通
  // hasComeEarlierThanは表示コンテントと共通
  // hasComeLaterThanは表示コンテントと共通
  // allocatablesは表示コンテントと共通
  // activeStateは表示コンテントと共通

  // シーン参照
  virtual void visit(RBAIsOn& exp) = 0;
  virtual void visit(RBAGetProperty& exp) = 0;

  virtual void visit(RBAIsTypeOfOperator& exp) = 0;

  // 演算子
  virtual void visit(RBAAndOperator& exp) = 0;
  virtual void visit(RBAOrOperator& exp) = 0;
  virtual void visit(RBANotOperator& exp) = 0;
  virtual void visit(RBAImpliesOperator& exp) = 0;
  virtual void visit(RBAIsEqualToOperator& exp) = 0;
  virtual void visit(RBAObjectCompare& exp) = 0;
  virtual void visit(RBAIsGreaterThanOperator& exp) = 0;
  virtual void visit(RBAIsGreaterThanEqualOperator& exp) = 0;
  virtual void visit(RBAIsLowerThanOperator& exp) = 0;
  virtual void visit(RBAIsLowerThanEqualOperator& exp) = 0;

  // 量化記号
  virtual void visit(RBAForAllOperator& exp) = 0;
  virtual void visit(RBAExistsOperator& exp) = 0;

  // 組込み定義式
  virtual void visit(RBAAllInstanceOfArea& exp) = 0;
  virtual void visit(RBAAllInstanceOfViewContent& exp) = 0;
  virtual void visit(RBAAllInstanceOfZone& exp) = 0;
  virtual void visit(RBAAllInstanceOfSoundContent& exp) = 0;

  // 構文
  virtual void visit(RBAIfStatement& exp) = 0;
  virtual void visit(RBALetStatement& exp) = 0;

  // 修飾子
  virtual void visit(RBAPreviousModifier& exp) = 0;

  // 集合操作
  virtual void visit(RBAMaxOperator& exp) = 0;
  virtual void visit(RBAMinOperator& exp) = 0;
  virtual void visit(RBASelectOperator& exp) = 0;
  virtual void visit(RBASizeOperator& exp) = 0;

  // オブジェクトリファレンス
  virtual void visit(RBAObjectReference& exp) = 0;
  virtual void visit(RBASetOfOperator& exp) = 0;
};

}

#endif
