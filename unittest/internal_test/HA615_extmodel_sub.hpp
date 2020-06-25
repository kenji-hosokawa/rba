// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA-615 Extension Model class
 */

#ifndef EXTENDMODEL_HPP
#define EXTENDMODEL_HPP

#include "RBAModelImpl.hpp"

namespace rba
{

class ExtModel : public RBAModelImpl
{
public:
  ExtModel();
  virtual ~ExtModel();

public:
  // override
  void addContent(const RBAContent* newContent);

  // extended
  void setAddContentFlag(bool flag);
  bool getAddContentFlag();

private:
  bool addContentFlag = false;

};

}

#endif

