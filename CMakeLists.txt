cmake_minimum_required(VERSION 3.6)
project(text_based_engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(DIRECTORY_SQLITE_CPP "SQLiteCpp")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.62.0 COMPONENTS system filesystem)

include_directories("${DIRECTORY_SQLITE_CPP}/include" "src/dependencies" "../_libs/sqlite3")
add_subdirectory(${DIRECTORY_SQLITE_CPP})

set(source_files_text_based_engine)
add_subdirectory(src)
add_executable(text_based_engine ${source_files_text_based_engine})

# Link text_based_engine with also pthread and dl for linux.
if (UNIX AND NOT APPLE)
    # Linux
    target_link_libraries(text_based_engine pthread dl)
elseif (UNIX AND APPLE)
    # Mac OS
    target_link_libraries(text_based_engine pthread)
else ()
    # Windows
    target_link_libraries(text_based_engine)
endif ()


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(text_based_engine ${Boost_LIBRARIES})
endif ()

target_link_libraries(text_based_engine sqlite3 SQLiteCpp tbe_engine)