/**
 * 影響情報クラス
 */

#ifndef RBAAFFECTINFO_HPP
#define RBAAFFECTINFO_HPP

#include <unordered_map>
#include <set>

namespace rba
{

class RBAAllocatable;

class RBAAffectInfo
{
public:
  RBAAffectInfo()=default;
  RBAAffectInfo(const RBAAffectInfo&)=delete;
  RBAAffectInfo(const RBAAffectInfo&&)=delete;
  RBAAffectInfo& operator=(const RBAAffectInfo&)=delete;
  RBAAffectInfo& operator=(const RBAAffectInfo&&)=delete;
  virtual ~RBAAffectInfo()=default;

public:
  bool alreadyKnowsThatFormerHasAffectedToLatter(const RBAAllocatable* const allocatable,
						 const RBAAllocatable* const affectAllocatable) const;
  void addInfoThatFormerAffectedToLatter(const RBAAllocatable* const allocatable,
					 const RBAAllocatable* const affectAllocatable);
  void removeAffectInfo(const RBAAllocatable* const affectAllocatable);

private:
  // アロケータブルが影響を与えた他アロケータブル情報
  mutable std::unordered_map<const RBAAllocatable*,
		   std::set<const RBAAllocatable*>>reaffected_;

};

}

#endif
