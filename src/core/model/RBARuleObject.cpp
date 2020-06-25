/**
 * ルールオプジェクトクラス定義ファイル
 */

#include <string>
#include <unordered_map>
#include "RBARuleObject.hpp"

namespace rba
{

RBARuleObject::RBARuleObject(const std::string& name)
  : RBANamedElement{name}
{
}

bool
RBARuleObject::isPrevious() const
{
  return false;
}

const RBARuleObject*
RBARuleObject::getRawObject() const
{
  return this;
}

void RBARuleObject::addTag(const std::string& tag)
{
  static_cast<void>(tags_.insert(tag));
}
  
bool RBARuleObject::containsTag(const std::string& tag) const
{
  return (tags_.find(tag) != tags_.end());
}

void RBARuleObject::addMember(RBARuleObject* member)
{
  members_[member->getElementName()] = member;
}

const RBARuleObject* RBARuleObject::getMember(const std::string& memberName) const
{
  if (members_.find(memberName) != members_.end()) {
    return (members_.at(memberName));
  } else {
    return nullptr;
  }
}

void RBARuleObject::addMember(const std::string& memberName, RBARuleObject* const val)
{
  members_[memberName] = val;
}

RBARuleObject*
RBARuleObject::getOwner() const
{
  return owner_;
}
  
void
RBARuleObject::setOwner(RBARuleObject* owner)
{
  owner_ = owner;
}

std::string
RBARuleObject::getUniqueName() const
{
  if (owner_ != nullptr) {
    // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
    // 【ルールに逸脱している内容】
    // getUniqueName()を再帰呼び出ししている
    // 【ルールを逸脱しても問題ないことの説明】
    // "コンテント名/ステートマシン名/状態名"といったオブジェクトがあるとき、
    // STATEMACHINE_STATEのowner_のSTATEMACHINEのowner_のCONTENTという順に再帰呼び出ししている。
    // ルールモデルの要素数は有限であり、循環関係にないため、スタックオーバーフローすることはなく、問題無い。
    return owner_->getUniqueName() + "/" + getElementName();
  }
  return getElementName();
}

const std::unordered_map<std::string, RBARuleObject*>& RBARuleObject::getMembers() const
{
  return members_;
}

}
