file(GLOB_RECURSE engine_source_files *.cpp *.h)

source_group(engine FILES ${engine_source_files})
add_library(engine ${engine_source_files})

target_link_libraries(engine SQLiteCpp)