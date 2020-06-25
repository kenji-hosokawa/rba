/// @file  RBAJsonElement.cpp
/// @brief JSONエレメントクラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAJsonElement.hpp"

#include "RBAArbitrationPolicy.hpp"
#include "RBAContentLoserType.hpp"
#ifdef RBA_USE_LOG
#include "RBAExpressionType.hpp"
#endif

namespace rba
{

// RBAJsonElementクラス

std::string RBAJsonElement::emptyStr_;

const std::string&
RBAJsonElement::getString() const
{
  // 派生クラスの関数がコールされるため、この関数がコールされることはない
  return emptyStr_;
}

std::int32_t
RBAJsonElement::getInt() const
{
  // 派生クラスの関数がコールされるため、この関数がコールされることはない
  return -99;
}

RBAArbitrationPolicy
RBAJsonElement::getArbitrationPolicy() const
{
  // 派生クラスの関数がコールされるため、この関数がコールされることはない
  return RBAArbitrationPolicy::DEFAULT;
}

RBAContentLoserType
RBAJsonElement::getLoserType() const
{
  // 派生クラスの関数がコールされるため、この関数がコールされることはない
  return RBAContentLoserType::NEVER_GIVEUP;
}

#ifdef RBA_USE_LOG
RBAExpressionType
RBAJsonElement::getExpressionType() const
{
  // 派生クラスの関数がコールされるため、この関数がコールされることはない
  return RBAExpressionType::VALUE;
}
#endif

void
RBAJsonElement::setName(const std::string& name)
{
  name_ = name;
}

const std::string&
RBAJsonElement::getName() const
{
  return name_;
}

void
RBAJsonElement::addChild(std::unique_ptr<RBAJsonElement> child)
{
  children_.push_back(move(child));
}

const std::vector<std::unique_ptr<RBAJsonElement>>&
RBAJsonElement::getChildren() const
{
  return children_;
}

RBAJsonElement*
RBAJsonElement::getChild() const
{
  return children_.front().get();
}

const RBAJsonElement*
RBAJsonElement::findChildren(const std::string& name) const
{
  RBAJsonElement* res{nullptr};
  for(const auto& elem : children_) {
    if(elem->getName() == name) {
      res = elem.get();
      break;
    }
  }

  return res;
}

const std::string&
RBAJsonElement::getClassName() const
{
  const RBAJsonElement* const elem {findChildren("class")};
  if(elem != nullptr) {
    return elem->getString();
  }

  return emptyStr_;
}

// RBAJsonElementElementクラス

RBAJsonElementElement::RBAJsonElementElement(const std::string& name)
  : RBAJsonElement{}
{
  setName(name);
}

// RBAJsonElementStringクラス

RBAJsonElementString::RBAJsonElementString(const std::string& name)
  : RBAJsonElement{}
{
  setName(name);
}

RBAArbitrationPolicy
RBAJsonElementString::getArbitrationPolicy() const
{
  if(str_ == "FIRST_COME_FIRST") {
    return RBAArbitrationPolicy::FIRST_COME_FIRST;
  }
  else if(str_ == "LAST_COME_FIRST") {
    return RBAArbitrationPolicy::LAST_COME_FIRST;
  }
  else if(str_ == "PRIORITY_FIRST_COME_FIRST") {
    return RBAArbitrationPolicy::PRIORITY_FIRST_COME_FIRST;
  }
  else if(str_ == "PRIORITY_LAST_COME_FIRST") {
    return RBAArbitrationPolicy::PRIORITY_LAST_COME_FIRST;
  }
  else {
    return RBAArbitrationPolicy::DEFAULT;
  }
}

RBAContentLoserType
RBAJsonElementString::getLoserType() const
{
  if(str_ == "GOOD_LOSER") {
    return RBAContentLoserType::GOOD_LOSER;
  }
  else if(str_ == "DO_NOT_GIVEUP_UNTIL_WIN") {
    return RBAContentLoserType::DO_NOT_GIVEUP_UNTIL_WIN;
  }
  else {
    return RBAContentLoserType::NEVER_GIVEUP;
  }
}

#ifdef RBA_USE_LOG
RBAExpressionType
RBAJsonElementString::getExpressionType() const
{
    if(str_ == "VALUE") {
      return RBAExpressionType::VALUE;
    }
    else if(str_ == "BOOLEAN") {
      return RBAExpressionType::BOOLEAN;
    }
    else if(str_ == "AREA") {
      return RBAExpressionType::AREA;
    }
    else if(str_ == "CONTENT") {
      return RBAExpressionType::CONTENT;
    }
    else if(str_ == "SOUND") {
      return RBAExpressionType::SOUND;
    }
    else if(str_ == "SET_OF_SOUND") {
      return RBAExpressionType::SET_OF_SOUND;
    }
    else if(str_ == "SET_OF_AREA") {
      return RBAExpressionType::SET_OF_AREA;
    }
    else if(str_ == "SET_OF_CONTENT") {
      return RBAExpressionType::SET_OF_CONTENT;
    }
    else if(str_ == "SET_OF_ZONE") {
      return RBAExpressionType::SET_OF_ZONE;
    }
    else if(str_ == "SCENE") {
      return RBAExpressionType::SCENE;
    }
    else if(str_ == "ZONE") {
      return RBAExpressionType::ZONE;
    }
    else if(str_ == "ACTION") {
      return RBAExpressionType::ACTION;
    }
    else if(str_ == "SET_OF_ACTION") {
      return RBAExpressionType::SET_OF_ACTION;
    }
    else {
      return RBAExpressionType::EXTENSION;
    }
}
#endif

const std::string&
RBAJsonElementString::getString() const
{
  return str_;
}

void
RBAJsonElementString::setString(const std::string& str)
{
  str_ = str;
}

// RBAJsonElementIntクラス

RBAJsonElementInt::RBAJsonElementInt(const std::string& name)
  : RBAJsonElement{}
{
  setName(name);
}

std::int32_t
RBAJsonElementInt::getInt() const
{
  return val_;
}

void
RBAJsonElementInt::setInt(const std::int32_t val)
{
  val_ = val;
}

// RBAJsonElementArrayクラス

RBAJsonElementArray::RBAJsonElementArray(const std::string& name)
  : RBAJsonElement{}
{
  setName(name);
}

}
