/**
 * 表示コンテントステート実装クラスヘッダファイル
 */

#ifndef RBAVIEWCONTENTSTATEIMPL_HPP
#define RBAVIEWCONTENTSTATEIMPL_HPP

#include <cstdint>
#include "RBAViewContentState.hpp"
#include "RBAContentState.hpp"

namespace rba
{

class RBAViewContentImpl;

class RBAViewContentStateImpl : public RBAViewContentState,
				public RBAContentState
{
public:
  explicit RBAViewContentStateImpl(const std::string& name="");
  RBAViewContentStateImpl(const RBAViewContentStateImpl&)=delete;
  RBAViewContentStateImpl(const RBAViewContentStateImpl&&)=delete;
  RBAViewContentStateImpl& operator=(const RBAViewContentStateImpl&)=delete;
  RBAViewContentStateImpl& operator=(const RBAViewContentStateImpl&&)=delete;
  virtual ~RBAViewContentStateImpl()=default;

public:
  std::string getName() const override;
  std::int32_t getPriority() const override;
  const RBAViewContent* getOwner() const override;
  std::int32_t getOrder() const override;
  std::string getUniqueName() const override;
  bool isViewContentState() const override;
  RBAModelElementType getModelElementType() const override;

};

}

#endif
