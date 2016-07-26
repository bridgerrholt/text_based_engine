/// @file command.cpp
/// Definition of the abstract class tbe::CommandBase.

#include "command.h"

#include <cassert>

#include <dep/print_line.h>
#include <dep/of_dynamic.h>

#include "../sql_support/types/include.h"

namespace {

using namespace tbe;

template <class T>
void
emplaceObject(CommandBase::ArgumentList & argList, T t)
{
  argList.emplace_back(new arg_types::Object {
    sql::DynamicVar { t }
  });
}



class ArgParser
{
  public:
    ArgParser(
      std::string::const_iterator       & i,
      std::string::const_iterator const   endSet,
      CommandBase::ArgumentList         & argList,
      std::locale                 const & localeSet) :

      end          { endSet },
      locale       { localeSet },
      i_           { i },
      argList_     { argList },
      currentList_ { &argList_ }
    {
      parse();
    }

    std::string::const_iterator const   end;
    std::locale                 const & locale;

    static
    CommandBase::ArgumentList
    parse(std::string::const_iterator       & i,
          std::string::const_iterator const   endSet,
          std::locale                 const & localeSet);

  private:
    void parse();

    void parseList(CommandBase::ArgumentList & argList);
    CommandBase::ArgumentList parseList();
    
    bool parseString();
    bool parseNumber();
    bool parseText();
    
    template <class T>
    void emplaceObject(T t) { ::emplaceObject(*currentList_, t); }

    std::string::const_iterator & i_;
    CommandBase::ArgumentList   & argList_;
    CommandBase::ArgumentList   * currentList_ { nullptr };
};



CommandBase::ArgumentList
ArgParser::parse(std::string::const_iterator       & i,
                 std::string::const_iterator const   endSet,
                 std::locale                 const & localeSet)
{
  CommandBase::ArgumentList argList;

  ArgParser parser { i, endSet, argList, localeSet };

  return argList;
}


void
ArgParser::parse()
{
  parseList(argList_);
}



void
ArgParser::parseList(CommandBase::ArgumentList & argList)
{
  auto oldList = currentList_;
  currentList_ = &argList;

  while (i_ != end) {
    if (std::isspace(*i_, locale))
      ++i_;

    else {
      if (parseString() ||
          parseNumber() ||
          parseText())
        ++i_;
      else
        throw std::runtime_error("Unexpected character");
    }
  }

  currentList_ = oldList;
}


CommandBase::ArgumentList
ArgParser::parseList()
{
  CommandBase::ArgumentList argList;
  parseList(argList);
  return argList;
}



bool
ArgParser::parseString()
{
  if (*i_ == '"' || *i_ == '\'') {
    std::string text;
    char        frontQuotation { *i_ };
    bool        foundEnd       { false };
    bool        escape         { false };

    while (i_ != end) {
      if (!escape) {
        if (*i_ == '\\') {
          escape = true;
          continue;
        }

        if (*i_ == frontQuotation) {
          foundEnd = true;
          break;
        }
      }

      else
        escape = false;

      text += *i_;
      ++i_;
    }

    assert(foundEnd);

    emplaceObject(new sql::types::Text { std::move(text) });

    return true;
  }

  else
    return false;
}



bool
ArgParser::parseNumber()
{
  if (std::isdigit(*i_, locale) || *i_ == '.') {
    std::string text;
    bool isFloat { false };

    while (i_ != end) {
      if (*i_ == '.') {
        if (isFloat) {
          throw std::runtime_error("Multiple periods within float");
        }
        else
          isFloat = true;
      }

      else if (std::isspace(*i_, locale)) {
        break;
      }

      else if (!std::isdigit(*i_, locale)) {
        throw std::runtime_error("Invalid character within number");
      }

      text += *i_;
      ++i_;
    }

    if (isFloat) {
      throw std::runtime_error("Floats are not supported");
    }
    else {
      emplaceObject(new sql::types::Int {
        std::stoi(text)
      });
    }

    return true;
  }

  else
    return false;
}



bool
ArgParser::parseText()
{
  if (std::isalpha(*i_, locale)) {
    std::string text;

    while (i_ != end) {
      if (std::isspace(*i_, locale))
        break;

      text += *i_;
      ++i_;
    }

    if (text == "true" || text == "false") {
      emplaceObject(new sql::types::Bool { (text == "true") });
    }
    else {
      currentList_->emplace_back(new arg_types::Option {
        std::move(text)
      });
    }

    return true;
  }

  else
    return false;
}



bool
checkString(std::string::const_iterator     & i,
            std::string::const_iterator const end,
            CommandBase::ArgumentList       & argList)
{
  if (*i == '"' || *i == '\'') {
    char frontQuotation { *i };
    bool foundEnd       { false };

    while (i != end) {
      ++i;
    }

    return true;
  }

  else
    return false;
}



}

namespace tbe {

CommandBase::CommandBase()
{

}


    
CommandBase::RunData
CommandBase::run(GameStateMap      & stateMap,
                 std::string const & args,
                 std::locale const & locale)
{
  auto       start { args.begin() };
  auto const end   { args.end() };
  ArgumentList argList = ::ArgParser::parse(start, end, locale);

  /*
  while (i != args.end()) {
    if (std::isspace(*i, locale)) {
      if (!nextArg.empty()) {
        auto j = nextArg.begin();

        if (*j == '"' || *j == '\'') {
          char startQuotation = *j;
          bool foundEndQuotation { false };

          while (j != nextArg.end()) {
            if (*j == startQuotation) {
              foundEndQuotation = true;
              break;
            }
            ++j;
          }

          if (!foundEndQuotation) {
            dep::printLine("Must have an ending quotation");
            return { INVALID, commands::NO_COMMAND, std::move(argList) };
          }

          ::emplaceObject(argList, new sql::types::Text {
            nextArg.substr(1, nextArg.size()-2)
          });
        }

        else {
          if (nextArg == "true" || nextArg == "false") {
            ::emplaceObject(argList, new sql::types::Bool {
              (nextArg == "true")
            });
          }
          else {
            argList.emplace_back(new arg_types::Option { nextArg });
          }
        }

        nextArg.clear();
      }
    }

    else {
      if (inText) {
        if (*i == frontQuotation) {
          inText = false;
          ::emplaceObject(argList, new sql::types::Text {
            nextArg
          });
        }
      }

      else if (*i == '"' || *i == '\'') {
        if (nextArg.empty()) {
          inText = true;
          frontQuotation = *i;
        }
      }

      else {
        nextArg += *i;
      }
    }

    ++i;
  }
  */


  bool incorrectSignature { false };
  if (argList.size() != getSignature().size()) {
    incorrectSignature = true;
  }

  else {
    for (ArgumentList::size_type i { 0 }; i < argList.size(); ++i) {
      if (argList[i]->kind != getSignature()[i]) {
        incorrectSignature = true;
        break;
      }
    }
  }

  if (incorrectSignature) {
    dep::printLine("Incorrect command signature");
    return { INVALID, getKindId(), std::move(argList) };
  }

  auto input = execute(stateMap, argList.begin(), argList.end());

  return { input, getKindId(), std::move(argList) };
}






}