/**
 * 音声コンテントステート実装クラスヘッダファイル
 */

#ifndef RBASOUNDCONTENTSTATEIMPL_HPP
#define RBASOUNDCONTENTSTATEIMPL_HPP

#include <cstdint>
#include "RBASoundContentState.hpp"
#include "RBAContentState.hpp"

namespace rba
{

class RBASoundContentImpl;

class RBASoundContentStateImpl : public RBASoundContentState,
				 public RBAContentState
{
public:
  explicit RBASoundContentStateImpl(const std::string& name="");
  RBASoundContentStateImpl(const RBASoundContentStateImpl&)=delete;
  RBASoundContentStateImpl(const RBASoundContentStateImpl&&)=delete;
  RBASoundContentStateImpl& operator=(const RBASoundContentStateImpl&)=delete;
  RBASoundContentStateImpl& operator=(const RBASoundContentStateImpl&&)=delete;
  virtual ~RBASoundContentStateImpl()=default;

public:
  bool isSoundContentState() const override;
  std::string getName() const override;
  std::int32_t getPriority() const override;
  const RBASoundContent* getOwner() const override;
  std::int32_t getOrder() const override;
  std::string getUniqueName() const override;
  RBAModelElementType getModelElementType() const override;

};

}

#endif
