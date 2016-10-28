file(GLOB_RECURSE engine_source_files *.cpp)
file(GLOB_RECURSE engine_header_files *.h)

source_group("Source Files" FILES ${engine_source_files})
source_group("Header Files" FILES ${engine_header_files})

add_library(tbe_engine ${engine_source_files} ${engine_header_files})

target_link_libraries(tbe_engine SQLiteCpp tbe_sql_support sqlite3)