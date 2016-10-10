cmake_minimum_required(VERSION 3.6)
project(text_based_engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(DIRECTORY_SQLITE_CPP "SQLiteCpp")
set(DIRECTORY_BOOST "../_libs/boost_1_62_0/build")

include_directories("${DIRECTORY_SQLITE_CPP}/include" "${DIRECTORY_BOOST}/include" "src/dependencies")
add_subdirectory(${DIRECTORY_SQLITE_CPP})

link_directories("${DIRECTORY_BOOST}/lib")

set(SOURCE_FILES
    src/dependencies/dep/basic_immutable_value.h
    src/dependencies/dep/check_file_exists.cpp
    src/dependencies/dep/check_file_exists.h
    src/dependencies/dep/input_manager.cpp
    src/dependencies/dep/input_manager.h
    src/dependencies/dep/is_int.cpp
    src/dependencies/dep/is_int.h
    src/dependencies/dep/load_to_string.cpp
    src/dependencies/dep/load_to_string.h
    src/dependencies/dep/of_dynamic.h
    src/dependencies/dep/ptr_to_string.h
    src/dependencies/dep/sleep_event.h
    src/dependencies/dep/string_formatter.cpp
    src/dependencies/dep/string_formatter.h
    src/dependencies/dep/value_key.h
    src/sql_support/column_info/basic_column_info.h
    src/sql_support/column_info/column_info.cpp
    src/sql_support/column_info/column_info.h
    src/sql_support/common/column_list_id.h
    src/sql_support/common/query_result.h
    src/sql_support/common/var_list.h
    src/sql_support/types/basic_type.h
    src/sql_support/types/include.h
    src/sql_support/types/int.h
    src/sql_support/types/kind.h
    src/sql_support/types/text.h
    src/sql_support/where_clause/expression.cpp
    src/sql_support/where_clause/expression.h
    src/sql_support/where_clause/expression_base.h
    src/sql_support/where_clause/expression_string.cpp
    src/sql_support/where_clause/expression_string.h
    src/sql_support/where_clause/where_clause.cpp
    src/sql_support/where_clause/where_clause.h
    src/sql_support/where_clause/where_clause_base.h
    src/sql_support/where_clause/where_clause_string.cpp
    src/sql_support/where_clause/where_clause_string.h
    src/sql_support/column_list.cpp
    src/sql_support/column_list.h
    src/sql_support/dynamic_query.cpp
    src/sql_support/dynamic_query.h
    src/sql_support/dynamic_type.cpp
    src/sql_support/dynamic_type.h
    src/sql_support/query.cpp
    src/sql_support/query.h
    src/sql_support/query_object.cpp
    src/sql_support/query_object.h
    src/ask_question.cpp
    src/ask_question.h
    src/database_structure.h
    src/engine.cpp
    src/engine.h
    src/main.cpp)

add_executable(text_based_engine ${SOURCE_FILES})

# Link SQLiteCpp_example1 with SQLiteCpp and sqlite3 (and also pthread and dl for linux)
if(UNIX AND NOT APPLE)
    # Linux
    target_link_libraries(text_based_engine SQLiteCpp sqlite3 pthread dl)
elseif(UNIX AND APPLE)
    # Mac OS
    target_link_libraries(text_based_engine SQLiteCpp sqlite3 pthread)
else()
    # Windows
    target_link_libraries(text_based_engine SQLiteCpp sqlite3)
endif()

target_link_libraries(text_based_engine libboost_filesystem libboost_system)