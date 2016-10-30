file(GLOB_RECURSE files dependencies/*)
list(APPEND files src/main.cpp)
set(source_files_text_based_engine ${files} PARENT_SCOPE)

add_subdirectory(engine)