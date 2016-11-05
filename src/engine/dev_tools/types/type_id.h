/// @file type_id.h
/// Definition of the enum tbe::dev_tools::types::TypeId.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_TYPE_ID_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_TYPE_ID_H

#include <string>

namespace tbe {
	namespace dev_tools {
		namespace types {


/// Expresses a certain engine type.
enum class TypeId
{
  BOOL,
  INT,
  STRING
};


		}
	}
}

#endif