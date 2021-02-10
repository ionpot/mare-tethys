set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(SDL2 REQUIRED)

add_library(common INTERFACE)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC"
OR "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
	# /W4 -> warning level 4
	# /WX -> warnings are errors
	target_compile_options(common INTERFACE /W4 /WX)
else()
	target_compile_options(common INTERFACE -Wall -Wextra -pedantic -Werror)
endif()

add_executable(tethys cfg_file.cpp config.cpp file.cpp log.cpp main.cpp sdl.cpp)

configure_file(tethys.cfg tethys.cfg COPYONLY)
configure_file(version.hpp.in version.hpp @ONLY)

# program can include version.hpp when compiling
target_include_directories(tethys PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(tethys PUBLIC "${SDL2_INCLUDE_DIRS}")

target_link_libraries(tethys PUBLIC common)
target_link_libraries(tethys PUBLIC "${SDL2_LIBRARIES}")