/**
 * モデルエレメントクラスヘッダファイル
 */

#ifndef RBAMODELELEMENT_HPP
#define RBAMODELELEMENT_HPP

#include <cstdint>
#include "RBADllExport.hpp"

namespace rba
{

enum class RBAModelElementType : std::uint8_t;

class DLL_EXPORT RBAModelElement
{
protected:
  RBAModelElement()=default;
  RBAModelElement(const RBAModelElement&)=delete;
  RBAModelElement(const RBAModelElement&&)=delete;
  RBAModelElement& operator=(const RBAModelElement&)=delete;
  RBAModelElement& operator=(const RBAModelElement&&)=delete;

public:
  virtual ~RBAModelElement()=default;

public:
  virtual void clearStatus();
  virtual RBAModelElementType getModelElementType() const;
  bool isModelElementType(const RBAModelElementType elemType) const;

};

}

#endif
