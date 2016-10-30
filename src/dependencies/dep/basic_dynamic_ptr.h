/// @file basic_dynamic_ptr.h
/// Declaration and definition of the class template dep::BasicDynamicPtr.

#ifndef _DEPENDENCIES_DEP_BASIC_DYNAMIC_PTR_H
#define _DEPENDENCIES_DEP_BASIC_DYNAMIC_PTR_H

namespace dep {
  
/// Provides helpful constructors to any smart pointer, meaning a lot less
/// repitition within construction of dynamic objects.
///
/// @tparam Ptr      Specialized smart pointer type to use.
/// @tparam Template Templated type that becomes specialized by the
///                  constructor. @ref Ptr must be able to point to it.
template <class Ptr, template <typename T> class Template>
class BasicDynamicPtr : public Ptr
{
  public:
    using PtrType = Ptr;

    BasicDynamicPtr() {}
    BasicDynamicPtr(Ptr ptr) : Ptr(std::move(ptr)) {}

    template <class T>
    BasicDynamicPtr(T data) :
      Ptr(new Template<T>(data)) {}
};

template <class Ptr, template <typename T> class Template, class T>
Ptr makeDynamicPtr(T data)
{
  return Ptr { new Template<T>(std::move(data)) };
}

}

#endif