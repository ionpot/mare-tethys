add_library(tethys_sdl base.cpp box.cpp event.cpp font.cpp hex_grid.cpp hexagon.cpp point.cpp rect.cpp renderer.cpp scroll.cpp size.cpp text_box.cpp texture.cpp window.cpp)

target_link_libraries(tethys_sdl PRIVATE tethys_util)

# SDL2 lib
find_package(SDL2 REQUIRED)
target_include_directories(tethys_sdl PUBLIC "${SDL2_INCLUDE_DIRS}")
target_link_libraries(tethys_sdl PUBLIC "${SDL2_LIBRARIES}")

# SDL2_image lib
find_package(SDL2_image REQUIRED)
target_include_directories(tethys_sdl PUBLIC "${SDL2_IMAGE_INCLUDE_DIRS}")
target_link_libraries(tethys_sdl PUBLIC "${SDL2_IMAGE_LIBRARIES}")

# SDL2_ttf lib
find_package(SDL2_ttf REQUIRED)
target_include_directories(tethys_sdl PUBLIC "${SDL2_TTF_INCLUDE_DIRS}")
target_link_libraries(tethys_sdl PUBLIC "${SDL2_TTF_LIBRARIES}")
