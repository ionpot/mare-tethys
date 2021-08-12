add_library(tethys_ui box.cpp hex_grid.cpp hex_textures.cpp text_box.cpp text_boxes.cpp)

target_link_libraries(tethys_ui PRIVATE tethys_util tethys_sdl)
