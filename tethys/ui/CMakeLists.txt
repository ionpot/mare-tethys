add_library(tethys_ui config.cpp hex_grid.cpp hex_info_boxes.cpp hex_textures.cpp)

target_link_libraries(tethys_ui PRIVATE tethys_util tethys_sdl)
