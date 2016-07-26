/// @file command_execution_info.h
/// Declarations of the abstract class tbe::CommandExecutionInfo.

#ifndef TEXT_BASED_ENGINE_ENGINE_COMMAND_EXECUTION_INFO_H
#define TEXT_BASED_ENGINE_ENGINE_COMMAND_EXECUTION_INFO_H

namespace tbe {

class CommandExecutionInfo
{
  public:

  private:

};



class CommandFail : CommandExecutionInfo
{
  public:
    bool hasNone   () const { return !invalid; }
    bool hasInvalid() const { return  invalid; }

  private:
    bool invalid;

};




class CommandSuccess : CommandExecutionInfo
{
  public:
    commands::Command command;
    ArgumentList      args;

  private:


};


}

#endif