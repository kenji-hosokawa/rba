/**
 * ビューコンテント実装クラスヘッダファイル
 */

#ifndef RBAVIEWCONTENTIMPL_HPP
#define RBAVIEWCONTENTIMPL_HPP

#include <string>
#include "RBAViewContent.hpp"
#include "RBAContent.hpp"

namespace rba
{

class RBAViewContentState;
class RBAArea;
class RBASize;
class RBASizeImpl;

class DLL_EXPORT RBAViewContentImpl : public RBAViewContent, public RBAContent
{
public:
  explicit RBAViewContentImpl(const std::string& name="");
  RBAViewContentImpl(const RBAViewContentImpl&)=delete;
  RBAViewContentImpl(const RBAViewContentImpl&&)=delete;
  RBAViewContentImpl& operator=(const RBAViewContentImpl&)=delete;
  RBAViewContentImpl& operator=(const RBAViewContentImpl&&)=delete;
  virtual ~RBAViewContentImpl()=default;

public:
  bool isViewContent() const override;
  std::string getName() const override;
  const std::list<const RBAViewContentState*>& getContentStates() const override;
  const std::list<const RBAArea*>& getAreas() const override;
  const std::list<const RBASize*>& getSizes() const override;
  RBAContentLoserType getLoserType() const override;

  void addSize(const RBASizeImpl* size);
  RBAModelElementType getModelElementType() const override;

  // Log
#ifdef RBA_USE_LOG
  std::string getSymbol() const override;
  std::string getVisibleSymbol() const override;
#endif

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  mutable std::list<const RBAArea*> externAreas_;
  mutable std::list<const RBASize*> externSizes_;
  mutable std::list<const RBAViewContentState*> externStates_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
