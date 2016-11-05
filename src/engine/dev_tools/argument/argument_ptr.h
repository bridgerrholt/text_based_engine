/// @file argument_ptr.h
/// Definition of the smart pointer tbe::dev_tools::argument::ArgumentPtr.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_ARGUMENT_PTR_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_ARGUMENT_PTR_H

#include <memory> // std::unique_ptr

#include "basic_argument.h"

namespace tbe {
	namespace dev_tools {
		namespace argument {


using ArgumentPtr = std::unique_ptr<ArgumentBase>;

/*
template <class T>
ArgumentPtr makeArgumentPtr(T data)
{
	return ArgumentPtr { new types::BasicArgument<T>(std::move(data)) };
}*/


		}
	}
}

#endif