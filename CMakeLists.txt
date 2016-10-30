cmake_minimum_required(VERSION 3.6)
project(text_based_engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(DIRECTORY_SQLITE_CPP "SQLiteCpp")
set(DIRECTORY_BOOST "D:/Bridger/Documents/Programming/C++/_libs/boost_1_62_0/build")

include_directories("${DIRECTORY_SQLITE_CPP}/include" "${DIRECTORY_BOOST}/include" "src/dependencies" "../_libs/sqlite3")
add_subdirectory(${DIRECTORY_SQLITE_CPP})

find_library(LIBBOOST_FILESYSTEM_LIBRARY libboost_filesystem HINTS ${DIRECTORY_BOOST}/lib)
find_library(LIBBOOST_SYSTEM_LIBRARY libboost_system HINTS ${DIRECTORY_BOOST}/lib)


set(source_files_text_based_engine)
add_subdirectory(src)
add_executable(text_based_engine ${source_files_text_based_engine})

# Link SQLiteCpp_example1 with SQLiteCpp and sqlite3 (and also pthread and dl for linux)
if(UNIX AND NOT APPLE)
    # Linux
    target_link_libraries(text_based_engine pthread dl)
elseif(UNIX AND APPLE)
    # Mac OS
    target_link_libraries(text_based_engine pthread)
else()
    # Windows
    target_link_libraries(text_based_engine)
endif()

target_link_libraries(text_based_engine sqlite3 SQLiteCpp ${LIBBOOST_FILESYSTEM_LIBRARY} ${LIBBOOST_SYSTEM_LIBRARY} tbe_engine)