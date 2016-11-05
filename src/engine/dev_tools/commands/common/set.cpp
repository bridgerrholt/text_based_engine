/// @file set.cpp
/// Definition of tbe::dev_tools::commands::Set.

#include "set.h"

#include <dep/of_dynamic.h>
#include "../../state_map.h"

namespace tbe {
	namespace dev_tools {
		namespace commands {

using namespace argument;

template <>
CommandBase::Signature
Set::signature_ = {
	ArgumentTypeId::OPTION,
	ArgumentTypeId::OBJECT
};



template <>
RunInfo::State
Set::execute(ExecutionArgs data)
{
	auto varName = dep::ofDynamic<Option>(data.i->get())->data;
	auto var = data.stateMap.getVariable(varName);
	++data.i;

	if (var) {
		auto setTo = dep::ofDynamic<Object>(data.i->get());
		if (var->get()->getTypeId() == setTo->data->getTypeId()) {
			//var->reset(std::move(setTo->data.get()));
			var->swap(setTo->data);
			return RunInfo::VALID;
		}
	}

	return RunInfo::INVALID;
}


		}
	}
}