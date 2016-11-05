/// @file list_paths.cpp
/// Definition of tbe::dev_tools::commands::ListPaths.

#include "list_paths.h"

namespace tbe {
	namespace dev_tools {
		namespace commands {


template <>
CommandBase::Signature
ListPaths::signature_ = {

};



template <>
RunInfo::State
ListPaths::execute(ExecutionArgs data)
{
	return RunInfo::INVALID;
}


		}
	}
}