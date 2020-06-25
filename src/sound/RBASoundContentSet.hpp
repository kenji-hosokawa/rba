/**
 * 音声コンテントセット実装クラスヘッダファイル
 */

#ifndef RBASOUNDCONTENTSET_HPP
#define RBASOUNDCONTENTSET_HPP

#include "RBAContentSet.hpp"
#include "RBADllExport.hpp"

namespace rba
{

class RBASoundContent;
class RBASoundContentImpl;

class DLL_EXPORT RBASoundContentSet : public RBAContentSet
{
public:
  explicit RBASoundContentSet(const std::string& name="");
  RBASoundContentSet(const RBASoundContentSet&)=delete;
  RBASoundContentSet(const RBASoundContentSet&&)=delete;
  RBASoundContentSet& operator=(const RBASoundContentSet&)=delete;
  RBASoundContentSet& operator=(const RBASoundContentSet&&)=delete;
  virtual ~RBASoundContentSet()=default;

public:
  const std::list<const RBASoundContent*>& getTargets() const;
  void addTarget(const RBAContent* content) override;
  void clear() override;
  RBAModelElementType getModelElementType() const override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBASoundContent*> externalContents_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
