/**
 * ディスプレイ実装クラスヘッダファイル
 */

#ifndef RBADISPLAYIMPL_HPP
#define RBADISPLAYIMPL_HPP

#include "RBADisplay.hpp"
#include "RBANamedElement.hpp"

namespace rba
{

class RBASizeImpl;
class RBAAreaImpl;

class RBADisplayImpl : public RBADisplay, public RBANamedElement
{
public:
  explicit RBADisplayImpl(const std::string& name);
  RBADisplayImpl(const RBADisplayImpl&)=delete;
  RBADisplayImpl(const RBADisplayImpl&&)=delete;
  RBADisplayImpl& operator=(const RBADisplayImpl&)=delete;
  RBADisplayImpl& operator=(const RBADisplayImpl&&)=delete;
  virtual ~RBADisplayImpl()=default;

public:
  std::string getName() const override;
  const RBASize* getSize() const override;
  const std::list<const RBAArea*>& getAreas() const override;

  void setSize(const RBASizeImpl* const newSize);
  void addArea(const RBAAreaImpl* area);
  const std::list<const RBAArea*>& getAreaImpls() const;

private:
  std::list<const RBAArea*> areas_;
  const RBASizeImpl* size_ {nullptr};

};

}

#endif
