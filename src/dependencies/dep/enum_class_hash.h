/// @file enum_class_hash.h
/// Declaration and definition of the functor class template dep::EnumClassHash.

#ifndef _DEPENDENCIES_DEP_ENUM_CLASS_HASH_H
#define _DEPENDENCIES_DEP_ENUM_CLASS_HASH_H

namespace dep {

class EnumClassHash
{
  public:
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

}

#endif