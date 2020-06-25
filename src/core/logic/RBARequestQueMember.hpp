/**
 * リクエストキュークラスヘッダーファイル
 */

#ifndef RBAREQUESTQUEMEMBER_HPP
#define RBAREQUESTQUEMEMBER_HPP

#include <cstdint>

namespace rba {

class RBAContentState;

class RBARequestQueMember {
 public:
  RBARequestQueMember(const RBAContentState* const contentState, const bool isOn, const std::uint32_t syncIndex);
  RBARequestQueMember()=delete;
  RBARequestQueMember(const RBARequestQueMember&)=delete;
  RBARequestQueMember(const RBARequestQueMember&&)=delete;
  RBARequestQueMember& operator=(const RBARequestQueMember&)=delete;
  RBARequestQueMember& operator=(const RBARequestQueMember&&)=delete;
  virtual ~RBARequestQueMember() = default;

  const RBAContentState* getContentState() const;
  bool isOn() const;
  std::uint32_t getSyncIndex() const;

 private:
  const RBAContentState* contentState_; /// 調停を要求されたコンテントステート
  bool isOn_;                           /// 表示・出力要求、または、シーンON要求か

  /// 調停同期Index
  /// 同じ値のQueMenberは同じタイミングで調停し、値が異なる場合は、差分調停する。
  /// execute(list,bool)の要求を受けたとき、listに含まれるコンテントはすべて同じ値になり、
  /// setContentState(ContentState, bool)の要求を2回受けたとき、1回目の要求と2回目の要求では異なる値になる。
  /// onRequestやonWithdrawnで作成されたときは、トリガとなった要求と同じ値になる。
  std::uint32_t syncIndex_;
};

}

#endif /* RBAREQUESTQUEMEMBER_HPP */
