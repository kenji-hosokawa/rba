/**
 * RBAViewMove.hpp
 */

#ifndef RBAVIEWMOVE_HPP
#define RBAVIEWMOVE_HPP

#include "RBAViewActionType.hpp"
#include "RBAViewAction.hpp"

namespace rba {

class RBAArea;
class RBAViewContent;
class RBAViewContentState;

class DLL_EXPORT RBAViewMove : public RBAViewAction
{
public:
  RBAViewMove(const RBAArea* const newFromArea, const RBAArea* const newToArea,
	      const RBAViewContentState* const newContentState);
  RBAViewMove(const RBAViewMove& viewMove);
  RBAViewMove(const RBAViewMove&&)=delete;
  RBAViewMove& operator=(const RBAViewMove&)=delete;
  RBAViewMove& operator=(const RBAViewMove&&)=delete;
  virtual ~RBAViewMove()=default;

  bool operator==(const RBAViewAction& viewAction) override;

public:
  const RBAArea* getFromArea() const override;
  const RBAArea* getToArea() const override;
  const RBAViewContent* getContent() const override;
  const RBAViewContentState* getContentState() const override;
  RBAViewActionType getViewActionType() const override;

private:
  const RBAArea* fromArea_ {nullptr};
  const RBAArea* toArea_ {nullptr};
  const RBAViewContentState* contentState_ {nullptr};

};

}

#endif
