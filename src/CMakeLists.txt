cmake_minimum_required(VERSION 3.10)

project(Collections VERSION 1.0.0)

file(GLOB source_files "*.c")
file(GLOB header_files "../include/*.h")

add_library(${PROJECT_NAME} SHARED ${source_files})
add_library(${PROJECT_NAME}_static STATIC ${source_files})

include_directories("../include")

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${header_files}")
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
  CACHE INTERNAL "${PROJECT_NAME}: Include directories" FORCE)

target_link_libraries(${PROJECT_NAME})

install( TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_static
  	ARCHIVE DESTINATION lib
  	LIBRARY DESTINATION lib
  	PUBLIC_HEADER DESTINATION include/${PROJECT_NAME} )
