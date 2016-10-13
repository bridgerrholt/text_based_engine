file(GLOB_RECURSE sql_support_source_files *.cpp)
file(GLOB_RECURSE sql_support_header_files *.h)

source_group("Source Files" FILES ${sql_support_source_files})
source_group("Header Files" FILES ${sql_support_header_files})

add_library(sql_support ${sql_support_source_files} ${sql_support_header_files})

target_link_libraries(sql_support SQLiteCpp)