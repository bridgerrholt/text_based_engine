# Text-Based Engine
An engine programmed in C++ that reads a database (SQLite) forming a text-based game. Version 1 is fully functional.

## Dependencies
### SQLite
SQLite front page is [here](https://www.sqlite.org/ "SQLite front page").
The SQLite amalgamation is the easiest way of using SQLite and the makefile already supports it. Simply download the most recent version (in this project, SQLite3 is the currently used version and pre-release is never tested) from [here](https://www.sqlite.org/download.html "SQLite download page") and drop `sqlite3.c` and `sqlite3.h` in a folder named `sqlite3` under `/src` (in other words, `/src/sqlite3`).

## Building
Running `make` under `/src` should be good enough, however MinGW does not seem to consistently work with SQLite and you may have to import all the implementation files into Visual Studio.

## Running
You must provide one of the demo databases (`.db` extension) found in `/demos` or your own database. It is also recommended to pipe the error stream to `/src/cerrlog.txt` because right now that stream is used heavily for debugging.

### Unix-type systems
`./text_based_engine ../demos/demo_0/interactions.db 2> cerrlog.txt`