file(GLOB root_source *.cpp)
file(GLOB root_header *.h)

file(GLOB dev_tools_source dev_tools/*.cpp)
file(GLOB dev_tools_header dev_tools/*.h)

file(GLOB_RECURSE dev_tools_argument_source dev_tools/argument/*.cpp)
file(GLOB_RECURSE dev_tools_argument_header dev_tools/argument/*.h)

file(GLOB_RECURSE dev_tools_commands_source dev_tools/commands/*.cpp)
file(GLOB_RECURSE dev_tools_commands_header dev_tools/commands/*.h)

file(GLOB_RECURSE dev_tools_types_source dev_tools/types/*.cpp)
file(GLOB_RECURSE dev_tools_types_header dev_tools/types/*.h)


source_group("Source Files" FILES ${root_source})
source_group("Header Files" FILES ${root_header})

source_group("Source Files\\dev_tools" FILES ${dev_tools_source})
source_group("Header Files\\dev_tools" FILES ${dev_tools_header})

source_group("Source Files\\dev_tools\\argument" FILES ${dev_tools_argument_source})
source_group("Header Files\\dev_tools\\argument" FILES ${dev_tools_argument_header})

source_group("Source Files\\dev_tools\\commands" FILES ${dev_tools_commands_source})
source_group("Header Files\\dev_tools\\commands" FILES ${dev_tools_commands_header})

source_group("Source Files\\dev_tools\\types" FILES ${dev_tools_types_source})
source_group("Header Files\\dev_tools\\types" FILES ${dev_tools_types_header})


add_library(tbe_engine
  ${root_source}               ${root_header}
  ${dev_tools_source}          ${dev_tools_header}
  ${dev_tools_argument_source} ${dev_tools_argument_header}
  ${dev_tools_commands_source} ${dev_tools_commands_header}
  ${dev_tools_types_source}    ${dev_tools_types_header}
)

target_link_libraries(tbe_engine SQLiteCpp sqlite3)