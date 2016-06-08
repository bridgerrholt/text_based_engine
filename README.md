# Text-Based Engine
An engine programmed in C++ that reads a database (SQLite) forming a text-based game.

## Dependencies
### SQLite
SQLite front page is [here](https://www.sqlite.org/ "SQLite front page").
The SQLite amalgamation is the easiest way of using SQLite and the makefile already supports it. Simply download the most recent version (in this project, SQLite3 is the currently used version and pre-release is never tested) from [here](https://www.sqlite.org/download.html "SQLite download page") and drop `sqlite3.c` and `sqlite3.h` in a folder named `sqlite3` under `src` (in other words, `/src/sqlite3/`).