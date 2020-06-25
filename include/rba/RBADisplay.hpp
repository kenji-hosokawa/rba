// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * Display class
 */

#ifndef RBADISPLAY_HPP
#define RBADISPLAY_HPP

#include <list>
#include <string>

namespace rba {

class RBAArea;
class RBASize;

/**
 * @class RBADisplay
 * Defines a screen layout of the display.<br>
 * You can define multiple displays for Multi-Display products.
 * Display defines a set of areas which are laid out on it.
 */
class RBADisplay
{
protected:
  RBADisplay()=default;
  RBADisplay(const RBADisplay&)=delete;
  RBADisplay(RBADisplay&&)=delete;
  RBADisplay& operator=(const RBADisplay&)=delete;
  RBADisplay& operator=(RBADisplay&&)=delete;
  ~RBADisplay()=default;

public:
  /**
   * @brief Returns the name of display
   * @return Display name
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the size of display
   * @return Size
   */
  virtual const RBASize* getSize() const=0;

  /**
   * @brief Returns areas which are allocated to the display
   * @return List of area
   */
  virtual const std::list<const RBAArea*>& getAreas() const=0;

};

}

#endif
