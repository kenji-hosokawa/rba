/**
 * RuleObjectのPrevious Wrapperクラスヘッダファイル
 */
#ifndef RBAPREVIOUSOBJECTWRAPPER_HPP
#define RBAPREVIOUSOBJECTWRAPPER_HPP

#include "RBARuleObject.hpp"

namespace rba
{

class DLL_EXPORT RBAPreviousObjectWrapper : public RBARuleObject
{
public:
  RBAPreviousObjectWrapper()=default;
  RBAPreviousObjectWrapper(const RBAPreviousObjectWrapper&)=delete;
  RBAPreviousObjectWrapper(const RBAPreviousObjectWrapper&&)=delete;
  RBAPreviousObjectWrapper& operator=(const RBAPreviousObjectWrapper&)=delete;
  RBAPreviousObjectWrapper& operator=(const RBAPreviousObjectWrapper&&)=delete;
  virtual ~RBAPreviousObjectWrapper()=default;

public:
  bool isPrevious() const override;
  const RBARuleObject* getRawObject() const override;
  void setRefObject(const RBARuleObject* const obj);

private:
  const RBARuleObject* refObject_ {nullptr};

};

}

#endif
