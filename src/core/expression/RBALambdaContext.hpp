/**
 * ラムダコンテキストクラスヘッダファイル
 */

#ifndef RBALAMBDACONTEXT_HPP
#define RBALAMBDACONTEXT_HPP

#include "RBASetOperator.hpp"

namespace rba
{

class RBALambdaExpression;

class DLL_EXPORT RBALambdaContext : public RBASetOperator
{
protected:
  RBALambdaContext()=default;
  RBALambdaContext(const RBALambdaContext&)=delete;
  RBALambdaContext(const RBALambdaContext&&)=delete;
  RBALambdaContext& operator=(const RBALambdaContext&)=delete;
  RBALambdaContext& operator=(const RBALambdaContext&&)=delete;
public:
  virtual ~RBALambdaContext()=default;

public:
  RBALambdaExpression* const getLambda() const;
  void setLambda(RBALambdaExpression* const newLambda);

#ifdef RBA_USE_LOG
  void createHierarchy() override;
#endif

private:
  RBALambdaExpression* lambda_ {nullptr};

};

}

#endif
