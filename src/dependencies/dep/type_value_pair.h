/// @file type_value_pair.h
/// Declaration of class template dep::TypeValuePair.

#ifndef _DEPENDENCIES_DEP_TYPE_VALUE_PAIR_H
#define _DEPENDENCIES_DEP_TYPE_VALUE_PAIR_H

#include <string>

namespace dep {
  
template <class T, class V, V v>
class TypeValuePair
{
	public:
		using Type           = T;
		static V const value = v;

		TypeValuePair() = delete;
};

}

#endif