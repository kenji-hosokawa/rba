// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA-615 Ext Model class
 */

#include "HA615_extmodel_sub.hpp"

namespace rba
{

ExtModel::ExtModel()
{
}

ExtModel::~ExtModel()
{
}

void
ExtModel::addContent(const RBAContent* newContent)
{
  addContentFlag = true;
  RBAModelImpl::addContent(newContent);
}

void
ExtModel::setAddContentFlag(bool flag)
{
  addContentFlag = flag;
}

bool
ExtModel::getAddContentFlag()
{
  return addContentFlag;
}

}
