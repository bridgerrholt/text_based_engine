/// @file of_static.h
/// Defines the ofStatic function.

#ifndef _DEPENDENCIES_DEP_OF_STATIC_H
#define _DEPENDENCIES_DEP_OF_STATIC_H

namespace dep {

/** Statically casts a given pointer to a pointer to a given type.
    Casts a pointer to an object of CastFrom to a pointer to an object of CastTo.

    @param[in] from Pointer to the CastFrom object.
    @return The statically casted pointer to a CastTo object.
*/
template <class CastTo, class CastFrom>
CastTo*
ofStatic(CastFrom& from)
{
  return static_cast<CastTo*>(&from);
}

template <class CastTo, class CastFrom>
CastTo*
ofStatic(CastFrom* from)
{
  return static_cast<CastTo*>(from);
}



/// Const version of ofStatic.
template <class CastTo, class CastFrom>
const CastTo*
ofStatic(const CastFrom& from)
{
  return static_cast<const CastTo*>(&from);
}

template <class CastTo, class CastFrom>
const CastTo*
ofStatic(const CastFrom* from)
{
  return static_cast<const CastTo*>(from);
}

}

#endif