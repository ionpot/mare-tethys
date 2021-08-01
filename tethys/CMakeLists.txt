set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC"
OR "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
	# /W4 -> warning level 4
	# /WX -> warnings are errors
	# /we4062 -> enable warning C4062 as an error
	add_compile_options(/W4 /WX /we4062)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# number of characters from absolute root to project root
# source files can use this to obtain the relative path
string(LENGTH "${PROJECT_SOURCE_DIR}/" BASE_DIR_LENGTH)
add_compile_definitions(TETHYS_BASE_DIR_LENGTH=${BASE_DIR_LENGTH})

# favour the <prefix/...> include syntax
include_directories("${CMAKE_CURRENT_LIST_DIR}")

# subdirectories
add_subdirectory(util)
add_subdirectory(sdl)
add_subdirectory(game)

# WIN32 flag removes the console window on Windows
add_executable(tethys WIN32 config.cpp grid_file.cpp grid_view.cpp hex_textures.cpp main.cpp screen.cpp)

# executable needs these at runtime
configure_file(tethys.cfg tethys.cfg COPYONLY)
configure_file(tethys.grid tethys.grid COPYONLY)

# project version/build numbers placed here
configure_file(version.hpp.in version.hpp @ONLY)

# program can include version.hpp when compiling
target_include_directories(tethys PRIVATE "${PROJECT_BINARY_DIR}")

# dependencies
target_link_libraries(tethys PRIVATE tethys_util tethys_sdl)

# copy assets dir next to the binary when compilation succeeds
add_custom_command(TARGET tethys POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/assets
		${CMAKE_CURRENT_BINARY_DIR}/assets)
