/// @file to_underlying_value.h
/// Definition of the function template dep::toUnderlyingValue().

#ifndef _DEPENDENCIES_DEP_TO_UNDERLYING_VALUE_H
#define _DEPENDENCIES_DEP_TO_UNDERLYING_VALUE_H

#include <sstream>

namespace dep {


/// Returns the underlying value of the passed object.
template <typename T>
auto toUnderlyingValue(T const object)
	-> typename std::underlying_type<T>::type
{
	return static_cast<typename std::underlying_type<T>::type>(object);
}


}

#endif
