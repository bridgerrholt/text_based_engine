/// @file argument.h
/// Declarations of the class tbe::ArgumentBase.

#ifndef TEXT_BASED_ENGINE_ENGINE_ARGUMENT_H
#define TEXT_BASED_ENGINE_ENGINE_ARGUMENT_H

#include <memory>
#include <string>

#include "../sql_support/common/var_list.h"

namespace tbe {

class ArgumentBase
{
  public:
    enum Kind
    {
      OBJECT = 1,
      OPTION
    };

    ArgumentBase(Kind kindSet);

    virtual
    ~ArgumentBase() = 0;

    Kind const kind;
};


typedef std::unique_ptr<ArgumentBase> DynamicArgument;



  namespace arg_types {

template <class T, ArgumentBase::Kind k>
class BasicArgument : public ArgumentBase
{
  public:
    BasicArgument(T t) : ArgumentBase(k)
    {
      data = std::move(t);
    }

    T data;
};


typedef BasicArgument<sql::DynamicVar, ArgumentBase::OBJECT> Object;
typedef BasicArgument<std::string,     ArgumentBase::OPTION> Option;

  }
}

#endif