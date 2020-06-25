// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * View content class
 */

#ifndef RBAVIEWCONTENT_HPP
#define RBAVIEWCONTENT_HPP

#include <list>
#include <string>
#include "RBAContentLoserType.hpp"

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

namespace rba
{

class RBAViewContentState;
class RBAArea;
class RBASize;
  
/**
 * @class RBAViewContent
 * Define the object of view content.<br>
 * View content has plural status.
 * When view contents connected to a area, active status is displayed.
 * Each object can define plural area which can displayed view contents.
 */
class DLL_EXPORT RBAViewContent
{
protected:
  RBAViewContent()=default;
  RBAViewContent(const RBAViewContent&)=delete;
  RBAViewContent(RBAViewContent&&)=delete;
  RBAViewContent& operator=(const RBAViewContent&)=delete;
  RBAViewContent& operator=(RBAViewContent&&)=delete;
  ~RBAViewContent()=default;

public:
  /**
   * @brief Returns the name of the view content.
   * @return View content name
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the state of the view content.
   * @return List of view content state
   */
  virtual const std::list<const RBAViewContentState*>& getContentStates() const=0;

  /**
   * @brief Returns the area of the view content.
   * @return List of the area
   */
  virtual const std::list<const RBAArea*>& getAreas() const=0;

  /**
   * @brief Returns the list of size assignment to this content.
   * @return List of size
   */
  virtual const std::list<const RBASize*>& getSizes() const=0;

  /**
   * @brief Returns the loser type.
   * @return Loser type
   */
  virtual RBAContentLoserType getLoserType() const=0;

public:
  /**
   * @brief Defines the default loser type.
   */
  const static RBAContentLoserType LOSER_TYPE_EDEFAULT =
    RBAContentLoserType::NEVER_GIVEUP;

};

}

#endif
