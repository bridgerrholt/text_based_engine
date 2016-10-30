file(GLOB root_source *.cpp)
file(GLOB root_header *.h)

file(GLOB dev_tools_source dev_tools/*.cpp)
file(GLOB dev_tools_header dev_tools/*.h)

file(GLOB dev_tools_commands_source dev_tools/commands/*.cpp)
file(GLOB dev_tools_commands_header dev_tools/commands/*.h)

file(GLOB_RECURSE dev_tools_type_system_source dev_tools/types/*.cpp)
file(GLOB_RECURSE dev_tools_type_system_header dev_tools/types/*.h)


source_group("Source Files" FILES ${root_source})
source_group("Header Files" FILES ${root_header})

source_group("Source Files\\dev_tools" FILES ${dev_tools_source})
source_group("Header Files\\dev_tools" FILES ${dev_tools_header})

source_group("Source Files\\dev_tools\\commands" FILES ${dev_tools_commands_source})
source_group("Header Files\\dev_tools\\commands" FILES ${dev_tools_commands_header})

source_group("Source Files\\dev_tools\\types" FILES ${dev_tools_type_system_source})
source_group("Header Files\\dev_tools\\types" FILES ${dev_tools_type_system_header})


add_library(tbe_engine
  ${root_source} ${root_header}
  ${dev_tools_source} ${dev_tools_header}
  ${dev_tools_commands_source} ${dev_tools_commands_header}
  ${dev_tools_type_system_source} ${dev_tools_type_system_header}
)

target_link_libraries(tbe_engine SQLiteCpp sqlite3)