#ifndef _DEPENDENCIES_DEP_FORMAT_STRING_H
#define _DEPENDENCIES_DEP_FORMAT_STRING_H

#include <locale>

#include <common/string_ref.h>

namespace dep {

class FormatString
{
  public:
    FormatString(std::locale const & locale,
                 com::StringRef      contents);

    std::string str() const;

    FormatString& trimLeft();

    FormatString& trimRight();

    FormatString& trim();


  private:
    std::locale const & locale_;

    std::string contents_;
};


std::string str(FormatString const & formatString);

  
}

#endif