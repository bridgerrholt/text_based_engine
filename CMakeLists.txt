cmake_minimum_required(VERSION 3.6)
project(text_based_engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(DIRECTORY_SQLITE_CPP "SQLiteCpp")
set(DIRECTORY_BOOST "../_libs/boost_1_62_0/build")

include_directories("${DIRECTORY_SQLITE_CPP}/include" "${DIRECTORY_BOOST}/include" "src/dependencies")
add_subdirectory(${DIRECTORY_SQLITE_CPP})

link_directories("${DIRECTORY_BOOST}/lib")

set(source_files_text_based_engine)
add_subdirectory(src)
add_executable(text_based_engine ${source_files_text_based_engine})

# Link SQLiteCpp_example1 with SQLiteCpp and sqlite3 (and also pthread and dl for linux)
if(UNIX AND NOT APPLE)
    # Linux
    target_link_libraries(text_based_engine SQLiteCpp sqlite3 pthread dl)
elseif(UNIX AND APPLE)
    # Mac OS
    target_link_libraries(text_based_engine SQLiteCpp sqlite3 pthread)
else()
    # Windows
    target_link_libraries(text_based_engine SQLiteCpp sqlite3)
endif()

target_link_libraries(text_based_engine libboost_filesystem libboost_system engine)