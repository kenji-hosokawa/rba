// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * ポジションコンテナクラス
 */

#ifndef RBAPOSITIONCONTAINER_HPP
#define RBAPOSITIONCONTAINER_HPP

#include <cstdint>
#include "RBABasePoint.hpp"

namespace rba
{

class RBAArea;

class RBAPositionContainer
{
protected:
  RBAPositionContainer()=default;
  RBAPositionContainer(const RBAPositionContainer&)=delete;
  RBAPositionContainer(RBAPositionContainer&&)=delete;
  RBAPositionContainer& operator=(const RBAPositionContainer&)=delete;
  RBAPositionContainer& operator=(RBAPositionContainer&&)=delete;
  ~RBAPositionContainer()=default;

public:
  /**
   * @cond japanese
   * @brief X座標を取得する
   * @return X座標の値
   * @endcond
   *
   * @cond english
   * @brief 
   * @param
   * @return 
   * @endcond
   */
  virtual std::int32_t getX() const=0;

  /**
   * @cond japanese
   * @brief Y座標を取得する
   * @return Y座標の値
   * @endcond
   *
   * @cond english
   * @brief 
   * @param
   * @return 
   * @endcond
   */
  virtual std::int32_t getY() const=0;

  /**
   * @cond japanese
   * @brief ベースポイントを取得する
   * @return ベースポイント
   * @endcond
   *
   * @cond english
   * @brief 
   * @param
   * @return 
   * @endcond
   */
  virtual RBABasePoint getBasePoint() const=0;

  /**
   * @cond japanese
   * @brief 割り当てられているエリアを取得する
   * @return 割り当てられているエリア
   * @endcond
   *
   * @cond english
   * @brief 
   * @param
   * @return 
   * @endcond
   */
  virtual const RBAArea* getArea() const=0;

public:
  /**
   * @cond japanese
   * @brief X座標のデフォルト値
   * @endcond
   *
   * @cond english
   * @brief 
   * @endcond
   */
  const static std::int32_t X_EDEFAULT=0;

  /**
   * @cond japanese
   * @brief Y座標のデフォルト値
   * @endcond
   *
   * @cond english
   * @brief 
   * @endcond
   */
  const static std::int32_t Y_EDEFAULT=0;

  /**
   * @cond japanese
   * @brief ベースポイントのデフォルト値
   * @endcond
   *
   * @cond english
   * @brief 
   * @endcond
   */
  const static RBABasePoint BASE_POINT_EDEFAULT=RBABasePoint::LEFT_TOP;

};

}

#endif
