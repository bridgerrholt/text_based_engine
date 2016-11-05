/// @file run_info.h
/// Definition of the class tbe::RunInfo

#include "run_info.h"

namespace tbe {
  namespace dev_tools {

RunInfo::RunInfo() :
  RunInfo(NONE)
{

}


RunInfo::RunInfo(State stateSet) :
  state     (stateSet),
  commandId (commands::CommandId::NONE)
{

}


RunInfo::RunInfo(State                  stateSet,
                 commands::CommandId    kindSet,
                 argument::ArgumentList argsSet) :
  state     (stateSet),
  commandId (kindSet),
  args      (std::move(argsSet))
{


}


  }
}