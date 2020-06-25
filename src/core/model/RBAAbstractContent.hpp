/**
 * RBAAbstractContent.hpp
 */

#ifndef RBAABSTRACTCONTENT_HPP
#define RBAABSTRACTCONTENT_HPP

#include "RBARuleObject.hpp"

namespace rba
{

class DLL_EXPORT RBAAbstractContent : virtual public RBARuleObject
{
protected:
  explicit RBAAbstractContent(const std::string& name="");
  RBAAbstractContent(const RBAAbstractContent&)=delete;
  RBAAbstractContent(const RBAAbstractContent&&)=delete;
  RBAAbstractContent& operator=(const RBAAbstractContent&)=delete;
  RBAAbstractContent& operator=(const RBAAbstractContent&&)=delete;

public:
  virtual ~RBAAbstractContent()=default;

};

}

#endif
