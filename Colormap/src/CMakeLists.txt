file(
        GLOB 
        libfiles
        *.cpp
        )


add_library (colormap 
SHARED
${libfiles})

target_compile_options(colormap PUBLIC -std=c++14 -Wall)

