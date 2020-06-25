/**
 * 影響情報クラス定義ファイル
 */

#include "RBAAffectInfo.hpp"

namespace rba
{

/**
 * アロケータブルが既に対象のアロケータブルに影響を与えているかを返す
 * @param allocatable 影響を与えるアロケータブル
 * @param affectAllocatable 影響を受けるアロケータブル
 * @return
 */
bool
RBAAffectInfo::alreadyKnowsThatFormerHasAffectedToLatter(const RBAAllocatable* const allocatable,
							 const RBAAllocatable* const affectAllocatable) const
{
  for(const auto& alloc : reaffected_[allocatable]) {
    if(alloc == affectAllocatable) {
      return true;
    }
  }
  return false;
}

/**
 * 影響情報を登録する
 * @param allocatable 影響を与えるアロケータブル
 * @param affectAllocatable 影響を受けるアロケータブル
 */
void
RBAAffectInfo::addInfoThatFormerAffectedToLatter(const RBAAllocatable* const allocatable,
						 const RBAAllocatable* const affectAllocatable)
{
  static_cast<void>(reaffected_[allocatable].insert(affectAllocatable));
}

/**
 * 指定したアロケータブルの指定再帰階層の調停で登録した、
 * 他アロケータブルが持つアロケータブルの影響情報を削除する
 * @param affectAllocatable
 */
void RBAAffectInfo::removeAffectInfo(const RBAAllocatable* const affectAllocatable)
{
  static_cast<void>(reaffected_.erase(affectAllocatable));
}

}
