cmake_minimum_required(VERSION 3.7)
project(kursovoi_project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(kursovoi_project ${SOURCE_FILES})
#find_package()
set (${NAME} /Users/Roman/CLionProjects/air_kursovoi_project)
set (LIB_DIR_LOCATION ${NAME}/lib)
find_library(SQLite3 NAMES sqlite3 PATHS ${LIB_DIR_LOCATION})
set(INCLUDE_DIRS ${NAME}/include)

target_link_libraries(kursovoi_project SQLite3)
target_include_directories(kursovoi_project PRIVATE ${INCLUDE_DIRS})
#target_link_libraries (kursovoi_project ${sqlite})
#link_libraries(${sqlite})

