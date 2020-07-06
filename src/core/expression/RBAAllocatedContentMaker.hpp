/// @file  RBAAllocatedContentMaker.hpp
/// @brief AllocatedContent object maker class header file
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAALLOCATEDCONTENTMAKER_HPP
#define RBAALLOCATEDCONTENTMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief AllocatedContentオブジェクト生成クラス
class RBAAllocatedContentMaker : public RBAOperatorMaker
{
public:
  RBAAllocatedContentMaker();
  RBAAllocatedContentMaker(const RBAAllocatedContentMaker&)=delete;
  RBAAllocatedContentMaker(const RBAAllocatedContentMaker&&)=delete;
  RBAAllocatedContentMaker& operator=(const RBAAllocatedContentMaker&)=delete;
  RBAAllocatedContentMaker& operator=(const RBAAllocatedContentMaker&&)=delete;
  virtual ~RBAAllocatedContentMaker()=default;

protected:
  /// @brief Empty instanciation
  /// @details Create an empty instance of unique_ptr in a derived class
  /// @return unique_ptr of instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif
