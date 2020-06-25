//
// コンテントの状態遷移管理クラス
//

#ifndef RBACONTENTSTATUS_HPP
#define RBACONTENTSTATUS_HPP
#include <cstdint>

#include "RBAContentStatusType.hpp"

namespace rba
{
class RBAContentState;

class RBAContentStatus
{
 public:
  RBAContentStatus()=default;
  //コピーコンストラクタは他クラスで使用しているためdefaultで定義
  RBAContentStatus(const RBAContentStatus&)=default;
  RBAContentStatus(const RBAContentStatus&&)=delete;
  //コピー代入演算子も他クラスで使用しているためdefaultで定義
  RBAContentStatus& operator=(const RBAContentStatus&)=default;
  RBAContentStatus& operator=(const RBAContentStatus&&)=delete;
  virtual ~RBAContentStatus()=default;
  void onRequest();
  void setStatusType(const RBAContentStatusType type);
  RBAContentStatusType getStatusType() const;
  bool isActive() const;
  bool isUndisplayed() const;
  bool isDisplayed() const;
  bool isStandby() const;
  bool hasBeenCanceled() const;
  bool hasBeenDisplayed() const;
 private:
  RBAContentStatusType status_ {RBAContentStatusType::NoRequest};
};

} /* namespace rba */

#endif /* RBACONTENTSTATUS_HPP */
