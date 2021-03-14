set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# WIN32 flag removes the console window on Windows
add_executable(tethys WIN32 cfg_file.cpp config.cpp file.cpp grid_file.cpp hex_grid.cpp hex_textures.cpp hexagon.cpp log.cpp main.cpp rect.cpp screen.cpp scroll.cpp sdl.cpp)

configure_file(tethys.cfg tethys.cfg COPYONLY)
configure_file(tethys.grid tethys.grid COPYONLY)
configure_file(version.hpp.in version.hpp @ONLY)

# program can include version.hpp when compiling
target_include_directories(tethys PUBLIC "${PROJECT_BINARY_DIR}")

# common flags
add_library(common INTERFACE)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC"
OR "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
	# /W4 -> warning level 4
	# /WX -> warnings are errors
	target_compile_options(common INTERFACE /W4 /WX)
else()
	target_compile_options(common INTERFACE -Wall -Wextra -pedantic -Werror)
endif()
target_link_libraries(tethys PUBLIC common)

# SDL2 lib
find_package(SDL2 REQUIRED)
target_include_directories(tethys PUBLIC "${SDL2_INCLUDE_DIRS}")
target_link_libraries(tethys PUBLIC "${SDL2_LIBRARIES}")
