/// @file command.cpp
/// Definition of the abstract class tbe::CommandBase.

#include "command_base.h"

#include <cassert>

#include <dep/print_line.h>
#include <dep/of_dynamic.h>

#include "../types/types.h"

#include "../argument/argument_types.h"

#include "../run_info.h"

#include "../state_map.h"

namespace {

using namespace tbe;
using namespace tbe::dev_tools;
using namespace tbe::dev_tools::argument;

template <class T>
void
emplaceObject(ArgumentList & argList, T t)
{
  argList.emplace_back(new Object {
    dev_tools::types::ObjectPtr { t }
  });
}



class ArgParser
{
  public:
    ArgParser(
      std::string::const_iterator       & i,
      std::string::const_iterator const   endSet,
      ArgumentList            & argList,
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
    ArgumentList
    parse(std::string::const_iterator       & i,
          std::string::const_iterator const   endSet,
          std::locale                 const & localeSet);

  private:
    void parse();

    void parseList(ArgumentList & argList);
    ArgumentList parseList();
    
    bool parseString();
    bool parseNumber();
    bool parseText();
    
    template <class T>
    void emplaceObject(T t) { ::emplaceObject(*currentList_, t); }

    std::string::const_iterator & i_;
    ArgumentList                & argList_;
    ArgumentList                * currentList_ { nullptr };
};



ArgumentList
ArgParser::parse(std::string::const_iterator       & i,
                 std::string::const_iterator const   endSet,
                 std::locale                 const & localeSet)
{
  ArgumentList argList;

  ArgParser parser { i, endSet, argList, localeSet };

  return argList;
}


void
ArgParser::parse()
{
  parseList(argList_);
}



void
ArgParser::parseList(ArgumentList & argList)
{
  auto oldList = currentList_;
  currentList_ = &argList;

  while (i_ != end) {
    if (std::isspace(*i_, locale))
      ++i_;

    else {
      if (parseString() ||
          parseNumber() ||
          parseText()) {
				if (i_ != end)
					++i_;
				else
					break;
			}
      else
        throw std::runtime_error("Unexpected character");
    }
  }

  currentList_ = oldList;
}


ArgumentList
ArgParser::parseList()
{
  ArgumentList argList;
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

    emplaceObject(new dev_tools::types::String { std::move(text) });

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
      emplaceObject(new dev_tools::types::Int {
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
      emplaceObject(new dev_tools::types::Bool { (text == "true") });
    }
    else {
      currentList_->emplace_back(new argument::Option {
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
            ArgumentList       & argList)
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
  namespace dev_tools {
		namespace commands {

CommandBase::CommandBase()
{

}


CommandBase::~CommandBase()
{

}


    
RunInfo
CommandBase::run(StateMap          & stateMap,
                 std::string const & args,
                 std::locale const & locale)
{
  auto       start = args.begin();
  auto const end   = args.end();
  ArgumentList argList = ::ArgParser::parse(start, end, locale);

  bool incorrectSignature { false };
  if (argList.size() != getSignature().size()) {
    incorrectSignature = true;
  }

  else {
    for (ArgumentList::size_type i { 0 }; i < argList.size(); ++i) {
      if (argList[i]->type != getSignature()[i]) {
        incorrectSignature = true;
        break;
      }
    }
  }

  if (incorrectSignature) {
    dep::printLine("Incorrect command signature");
    return { RunInfo::INVALID, getCommandId(), std::move(argList) };
  }

  auto input = execute({stateMap, argList.begin(), argList.end()});

  return { input, getCommandId(), std::move(argList) };
}




		}
  }
}