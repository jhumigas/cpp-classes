# Make sure the compiler can find include files from our library.
include_directories (${CMAKE_SOURCE_DIR}/src)

# Define our examples to compile
file(
	GLOB 
	usage_examples
	*.cpp
	)



# loop over the list to compile them
foreach(f ${usage_examples})
	get_filename_component(exampleName ${f} NAME_WE) 
	add_executable (${exampleName} ${f}) 
	target_compile_options(${exampleName} PUBLIC -std=c++14 -Wall)
	target_link_libraries(${exampleName} colormap)
	add_dependencies(${exampleName} colormap)
endforeach(f)
