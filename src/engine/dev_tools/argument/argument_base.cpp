/// @file argument_base.cpp
/// Definition of the abstract base class tbe::dev_tools::argument::ArgumentBase.

#include "argument_base.h"

namespace tbe {
	namespace dev_tools {
		namespace argument {


ArgumentBase::ArgumentBase(ArgumentTypeId typeSet) :
	type {typeSet}
{

}



ArgumentBase::~ArgumentBase()
{

}



		}
	}
}