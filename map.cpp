#include "map.hpp"

#define FILENAME "./sprite/level/tile"

Map::Map() {}

Map::Map(SDL_Renderer* sdl_renderer) : m_renderer(sdl_renderer) {}

Map::~Map() {}

void Map::init_Map() {

}

SDL_Texture* Map::load_Texture(std::string filename) {
    SDL_Texture* texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", filename);
    texture = IMG_LoadTexture(m_renderer, filename.c_str());
    return texture;
}

void Map::load_Tiles() {
    for (int i = 0; i < MAX_TILE_TYPES; i++){
        std::string filename = FILENAME;
        std::string extension = i + ".bmp";
        filename = filename + extension;
        m_tile_textures_arr[i] = load_Texture(filename);
    }
}