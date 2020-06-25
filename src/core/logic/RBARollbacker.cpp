/**
 * 調停結果ロールバッククラス定義ファイル
 */

#include "RBARollbacker.hpp"
#include "RBAModelImpl.hpp"
#include "RBABackUpAllocatable.hpp"
#include "RBAArbitrator.hpp"

namespace rba
{

RBARollbacker::~RBARollbacker() noexcept
{
  children_.clear();
}

void
RBARollbacker::addChild(const std::shared_ptr<RBARollbacker> child)
{
  children_.push_back(child);
}

void
RBARollbacker::removeChild(const std::shared_ptr<RBARollbacker> child)
{
  children_.remove(child);
}

void
RBARollbacker::backup(std::list<const RBAAllocatable*>& backuplist)
{
  backupMap_.clear();
  for(const RBAAllocatable* const original : backuplist) {
    std::unique_ptr<RBAAllocatable> backupObj
      {std::make_unique<RBABackUpAllocatable>("backup_"
                                               + original->getElementName())};
    copyAllocatable(original, backupObj.get());
    backupMap_[original] = std::move(backupObj);
  }
}

void
RBARollbacker::rollback()
{
  for (auto& Child : children_) {
    // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
    // 【ルールに逸脱している内容】
    // rollback()を再帰呼び出ししている
    // 【ルールを逸脱しても問題ないことの説明】
    // 再調停のネストが深くなる毎にRBARollbackerが作成されるが、再調停には無限ループ防止処理を入れているため、
    // スタックオーバーフローすることはなく、問題無い。
    Child->rollback();
  }
  for(auto itr = backupMap_.begin(); itr != backupMap_.end(); ++itr) {
    const RBAAllocatable* const original {itr->first};
    const RBAAllocatable* const backupVal {itr->second.get()};
    copyAllocatable(backupVal, const_cast<RBAAllocatable*>(original));
  }
}

void
RBARollbacker::copyAllocatable(const RBAAllocatable* const from,
			       RBAAllocatable* const to)
{
  to->setHiddenChecked(from->isHiddenChecked());
  to->setHidden(from->isHidden());
  to->setChecked(from->isChecked());
  to->setState(from->getState());
  to->clearAllocatablesAffectedByYou();
  for(const RBAAllocatable* const allocatable : from->getAllocatablesAffectedByYou()) {
    to->addAllocatableWhichHasBeenAffectedByYou(allocatable);
  }
  to->setAttenuateChecked(from->isAttenuateChecked());
  to->setAttenuated(from->isAttenuated());
}

}
