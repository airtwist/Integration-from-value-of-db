cmake_minimum_required(VERSION 3.7)
project(kursovoi_project)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.c)
add_executable(kursovoi_project ${SOURCE_FILES})
set(SQLITE sqlite3.h)
#add_library(sqlite ${SQLITE})
#target_link_libraries(main.c sqlite3.h)

