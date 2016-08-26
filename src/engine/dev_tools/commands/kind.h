/// @file kind.h
/// Declaration of the enum tbe::commands::Kind.

#ifndef TEXT_BASED_ENGINE_ENGINE_COMMANDS_KIND_H
#define TEXT_BASED_ENGINE_ENGINE_COMMANDS_KIND_H

namespace tbe {
  namespace commands {

enum Kind
{
  NO_COMMAND = 0,

  QUIT,
  LIST_PATHS,
  DEV_ON,

  SET
};

  }
}

#endif