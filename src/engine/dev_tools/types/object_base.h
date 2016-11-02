/// @file type_base.h
/// Declaration of the abstract base class tbe::dev_tools::types::ObjectBase.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPE_BASE_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPE_BASE_H

#include "type_id.h"

namespace tbe {
	namespace dev_tools {
		namespace types {


/// Base class for all the engine's objects.
class ObjectBase
{
	public:
		/// Primary constructor.
		/// @param typeId Sets the underlying TypeId (@ref typeId_).
		ObjectBase(TypeId typeId);

		virtual
			~ObjectBase() = 0;

		/// Returns the id of the type (@ref typeId_).
		TypeId getTypeId() const { return typeId_; }


	private:
		/// Used for determining what type the object is.
		/// May be replaced with a pure virtual function instead.
		TypeId typeId_;
};


		}
	}
}

#endif




