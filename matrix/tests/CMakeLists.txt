include_directories (${CMAKE_SOURCE_DIR}/src)

file(GLOB 
  matrix_tests
  test-*.cpp)

foreach(filename ${matrix_tests})
  get_filename_component(testName ${filename} NAME_WE) 
  add_executable (${testName} ${filename}) 
  target_compile_options(${testName} PUBLIC -std=c++14 -Wall)
  target_link_libraries(${testName} matrix)
  install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${testName}
    DESTINATION bin
    RENAME ${CMAKE_PROJECT_NAME}-${testName})
endforeach(filename)
