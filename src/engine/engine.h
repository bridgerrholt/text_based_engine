/// @file engine.h
/// Declaration of the class tbe::Engine.

#ifndef TEXT_BASED_ENGINE_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_ENGINE_H

#include <locale>
#include <string>
#include <unordered_map>

#include <dep/input_manager.h>
#include <dep/sleep_event.h>
#include <dep/enum_class_hash.h>

//#include "../sql_support/common/query_result.h"

//#include "../sql_support/column_list.h"
//#include "../sql_support/database_handle.h"

#include "dev_tools/commands/command_id.h"
#include "dev_tools/command_processor.h"
//#include "dev_tools/game_state_map.h"

#include <SQLiteCpp/SQLiteCpp.h>

#include "ask_question.h"

namespace tbe {


class RunInfo;
class EngineData;

/// Provides the program's primary functionality.
/// An Engine object is used to load a given database and run the database's described game.
class Engine
{
	public:
		/// Default constructor.
		/// Doesn't actually load anything.
		Engine();

		/// Allows for a non-default locale.
		/// Called by all other constructors.
		/// @param[in] locale The explicitally-specified locale.
		Engine(std::locale locale);

		/// Highest-level constructor.
		/// Meant to take in the supplied terminal commands. Opens the database if provided,
		/// otherwise asks for one. Then calls run().
		Engine(int argc, char* argv[]);

		/// Unloads the database (if opened) and all active queries.
		~Engine();

		/// Ensures there is a database then calls run().
		void run(int argc, char* argv[]);

		/// Calls loadDatabase() then run().
		/// @param[in] fileName The database file to be passed to loadDatabase().
		void run(std::string const & fileName);

		/// Changes the locale.
		void setLocale(std::locale locale);


	private:
		std::string loadRoot() const;

		std::unique_ptr<EngineData> data_;
};


}

#endif