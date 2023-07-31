project(revelation)
cmake_minimum_required (VERSION 3.11)

add_definitions(-std=c++11)

aux_source_directory(revelation/src PROJ_SRC)

add_executable(${PROJECT_NAME} ${PROJ_SRC})

add_subdirectory(dep/libhv)
target_link_libraries(${PROJECT_NAME} hv_static)
