file(GLOB_RECURSE files dependencies/* sql_support/*)
set(source_files_text_based_engine ${files} PARENT_SCOPE)

add_subdirectory(engine)
add_subdirectory(sql_support)