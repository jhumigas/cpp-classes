file(GLOB 
  lib_sources
  matrix*.cpp)

file(GLOB 
  lib_headers
  matrix*.hpp)

add_library(matrix
  SHARED
  ${lib_sources})
target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options    (matrix PUBLIC -std=c++14 -Wall)

install(TARGETS matrix          DESTINATION lib                          )
install(FILES   ${lib_headers} DESTINATION include/${CMAKE_PROJECT_NAME})

