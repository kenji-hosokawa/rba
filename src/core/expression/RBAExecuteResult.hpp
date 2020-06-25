/**
 * 調停負け時の要求を取り下げるタイプ
 */

#ifndef RBAEXECUTERESULT_HPP
#define RBAEXECUTERESULT_HPP

namespace rba
{

enum class RBAExecuteResult : std::uint8_t
{
  TRUE,
  FALSE,
  EXE,    //doAction()でアクションを行った場合(SetOfActionとIfActionは対象外)
  NOTEXE, //doAction()でアクションを行わなかった場合(SetOfActionとIfActionは対象外)
  SKIP    //getValue(), getReferenceObject()の場合はSKIP
};

}

#endif
