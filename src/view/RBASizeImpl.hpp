/**
 * サイズ情報実装クラスヘッダファイル
 */

#ifndef RBASIZEIMPL_HPP
#define RBASIZEIMPL_HPP

#include "RBASize.hpp"
#include "RBANamedElement.hpp"

namespace rba
{

class RBASizeImpl : public RBASize, public RBANamedElement
{
public:
  explicit RBASizeImpl(const std::string& name="");
  RBASizeImpl(const RBASizeImpl&)=default;
  RBASizeImpl(RBASizeImpl&&)=default;
  RBASizeImpl& operator=(const RBASizeImpl&)=default;
  RBASizeImpl& operator=(RBASizeImpl&&)=default;
  virtual ~RBASizeImpl()=default;

public:
  std::string getName() const override;
  std::int32_t getWidth() const override;
  std::int32_t getHeight() const override;

  void setWidth(const std::int32_t newWidth);
  void setHeight(const std::int32_t newHeight);

  std::int32_t diff(const RBASizeImpl* const size) const;

private:
  std::int32_t width_ {WIDTH_EDEFAULT};
  std::int32_t height_ {HEIGHT_EDEFAULT};

};

}

#endif
