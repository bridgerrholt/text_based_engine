/// @file of_dynamic.h
/// Defines the ofDynamic function.

#ifndef _DEPENDENCIES_DEP_OF_DYNAMIC_H
#define _DEPENDENCIES_DEP_OF_DYNAMIC_H

#include <stdexcept>

namespace dep {

/** Dynamically casts a given pointer to a pointer to a given type.
    Casts a pointer to an object of CastFrom to a pointer to an object of CastTo. Throws an error
    if the cast failed.

    @param[in] from Pointer to the CastFrom object.
    @return The statically casted pointer to a CastTo object.
*/
template <class CastTo, class CastFrom>
CastTo*
ofDynamic(CastFrom* from)
{
  CastTo* returnPtr = dynamic_cast<CastTo*>(from);
  if (returnPtr)
    return returnPtr;
  else
    throw std::runtime_error("Invalid dynamic_cast within function"
      "ofDynamic<CastTo, CastFrom>(CastFrom& from)");
}

template <class CastTo, class CastFrom>
CastTo*
ofDynamic(CastFrom& from)
{
  return ofDynamic<CastTo>(&from);
}



/// Const version of ofDynamic.
template <class CastTo, class CastFrom>
const CastTo*
ofDynamic(const CastFrom* from)
{
  CastTo* returnPtr = dynamic_cast<const CastTo*>(from);
  if (returnPtr)
    return returnPtr;
  else
    throw std::runtime_error("Invalid dynamic_cast within function"
      "ofDynamic<CastTo, CastFrom>(CastFrom& from)");
}

template <class CastTo, class CastFrom>
const CastTo*
ofDynamic(const CastFrom& from)
{
  return ofDynamic<CastTo>(&from);
}



}

#endif