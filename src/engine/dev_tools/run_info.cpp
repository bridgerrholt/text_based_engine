/// @file run_info.h
/// Definition of the class tbe::RunInfo

#include "run_info.h"

namespace tbe {

RunInfo::RunInfo() :
  RunInfo(NONE)
{

}


RunInfo::RunInfo(State stateSet) :
  state {stateSet},
  kind  {commands::NO_COMMAND}
{

}


RunInfo::RunInfo(State          stateSet,
                 commands::Kind kindSet,
                 ArgumentList   argsSet) :
  state {stateSet},
  kind  {kindSet},
  args  (std::move(argsSet))
{


}

}