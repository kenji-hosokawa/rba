/**
 * A type that withdraws requests when arbitration loses
 */

#ifndef RBAEXECUTERESULT_HPP
#define RBAEXECUTERESULT_HPP

namespace rba
{

enum class RBAExecuteResult : std::uint8_t
{
  TRUE,
  FALSE,
  EXE,    //In case of action is performed by doAction() (Excludes SetOfAction and IfAction)
  NOTEXE, //In case of action is NOT performed　by doAction() (Excludes SetOfAction and IfAction)
  SKIP    //In case of getValue() or getReferenceObject()
};

}

#endif
