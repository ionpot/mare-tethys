add_library(tethys_ui hex_grid.cpp hex_info_boxes.cpp hex_textures.cpp hud.cpp)

target_link_libraries(tethys_ui PRIVATE tethys_util tethys_sdl)
