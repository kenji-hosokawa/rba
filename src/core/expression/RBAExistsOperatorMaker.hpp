/// @file  RBAExistsOperatorMaker.hpp
/// @brief ExistsOperator object maker Class header
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAEXISTSOPERATORMAKER_HPP
#define RBAEXISTSOPERATORMAKER_HPP

#include "RBALambdaContextMaker.hpp"

namespace rba
{

/// @brief ExistsOperator object maker Class
class RBAExistsOperatorMaker : public RBALambdaContextMaker
{
public:
  RBAExistsOperatorMaker();
  RBAExistsOperatorMaker(const RBAExistsOperatorMaker&)=delete;
  RBAExistsOperatorMaker(const RBAExistsOperatorMaker&&)=delete;
  RBAExistsOperatorMaker& operator=(const RBAExistsOperatorMaker&)=delete;
  RBAExistsOperatorMaker& operator=(const RBAExistsOperatorMaker&&)=delete;
  virtual ~RBAExistsOperatorMaker()=default;

protected:
  /// @brief Create empty instance
  /// @details Create an empty instance of unique_ptr in a derived class
  /// @return unique_ptr of instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

  /// @brief Set attributes of model element for each derived class
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model Model for storing created object
  /// @param[in,out] owner parent object(Not in use)
  RBAModelElement* setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner) override;

  /// @brief Crate empty object of LambdaContext
  /// @details Create empty object of unique_ptr
  /// @return unique_ptr for LambdaContext object
  std::unique_ptr<RBALambdaContext> createLambdaContext() override;

};

}

#endif
