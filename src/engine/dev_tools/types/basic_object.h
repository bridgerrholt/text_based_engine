/// @file basic_object.h
/// Definition of the class template tbe::dev_tools::types::BasicObject.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_BASIC_OBJECT_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_BASIC_OBJECT_H

#include <string>

#include "object_base.h"

#include "match_to_type_id.h"

namespace tbe {
	namespace dev_tools {
		namespace types {


/// Class template to be used for all the supported SQL types.
/// @tparam T The underlying type to use for representing the SQL type.
/// @tparam k The name (within the enum TypeId) for identification.
template <class T, TypeId id = matchToTypeId<T>()>
class BasicObject : public ObjectBase
{
	public:
		/// Allows usage of the type elsewhere.
		typedef T DataType;

		/// Primary constructor.
		/// @param[in] dataSet Moves into @ref data.
		BasicObject(DataType dataSet) : ObjectBase(id)
		{
			data = std::move(dataSet);
		}

		/// The underlying data.
		DataType data;
};


		}
	}
}

#endif