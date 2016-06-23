#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_TEMPLATE_QUERY_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_TEMPLATE_QUERY_H

#include <iostream>

#include <vector>
#include <tuple>

#include <com/string_ref.h>

#include "query.h"
#include "query_data.h"

namespace tbe {
  namespace sql {


void f();

template <class T, class ... Us>
void f(T a, Us ... pargs)
{
  std::cout << a << '\n';
  f(pargs ...);
}




template <class T, class ... Ts>
class TemplateQuery
{
  public:
    TemplateQuery(T t, Ts ... args)
    {
      f(t, args ...);
    }
};



template <class ... Ts>
class Object
{
  public:
    Object(Ts ... packSet)
    {
      buildStart(packSet ...);
    }

    void build() {}

    template <size_t index, class T, class ... Us>
    void build(T t, Us ... args)
    {
      std::cout << t << '\n';
      std::get<index>(pack) = t;
      build<index+1>(args ...);
    }

    template <class T, class ... Us>
    void buildStart(T t, Us ... pargs)
    {
      build<0>(t, pargs ...);
    }

    std::tuple<Ts ...> pack;

  private:

};



  }
}

#endif