/**
 * 名前要素クラスヘッダファイル
 */

#ifndef RBANAMEDELEMENT_HPP
#define RBANAMEDELEMENT_HPP

#include <string>
#include "RBAModelElement.hpp"

namespace rba
{

class DLL_EXPORT RBANamedElement : public RBAModelElement
{
protected:
  explicit RBANamedElement(const std::string& newName = "");
  RBANamedElement(const RBANamedElement&)=delete;
  RBANamedElement(const RBANamedElement&&)=delete;
  RBANamedElement& operator=(const RBANamedElement&)=delete;
  RBANamedElement& operator=(const RBANamedElement&&)=delete;

public:
  virtual ~RBANamedElement()=default;
  virtual std::string getUniqueName() const;
  const std::string& getElementName() const;
  const std::string& getDynamicName() const;
  void setDynamicName(const std::string& newName);

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  const std::string name_;
  std::string dynamic_name_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
