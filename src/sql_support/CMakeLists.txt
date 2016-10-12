file(GLOB_RECURSE sql_support_source_files *.cpp *.h)

source_group(sql_support FILES ${sql_support_source_files})
add_library(sql_support ${sql_support_source_files})

target_link_libraries(sql_support SQLiteCpp)