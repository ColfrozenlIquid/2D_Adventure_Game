#include "map.hpp"

#define FILENAME "./sprite/level/tile"

Map::Map() {}

Map::Map(SDL_Renderer* sdl_renderer) : m_renderer(sdl_renderer) {
    init_Map();
}

Map::~Map() {}

void Map::init_Map() {
    printf("Loading tiles");
    load_Tiles();
}

void Map::draw_Map() {
    for (int y = 0; y < MAP_RENDER_HEIGHT; y++) {
        for (int x = 0; x < MAP_RENDER_WIDTH; x++) {
            int n = m_map_data[x][y];
            switch (n) {
            case 0:
                blit_Texture(m_tile_textures_arr[n], x * TILE_SIZE, y * TILE_SIZE);
                break;
            case 1:
                blit_Texture(m_tile_textures_arr[n], x * TILE_SIZE, y * TILE_SIZE);
                break;
            }
        }
    }
}

SDL_Texture* Map::load_Texture(std::string filename) {
    SDL_Texture* texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", filename);
    texture = IMG_LoadTexture(m_renderer, filename.c_str());
    return texture;
}

void Map::load_Tiles() {
    for (int i = 0; i < MAX_TILE_TYPES; i++){
        std::string filename = FILENAME + std::to_string(i) + ".bmp";
        m_tile_textures_arr[i] = load_Texture(filename);
    }
}

void Map::blit_Texture(SDL_Texture* texture, int x_pos, int y_pos) {
    SDL_Rect destination;
    destination.x = x_pos;
    destination.y = y_pos;

    if (SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h) < 0) {
        printf("Failed to query texture of map: %s", SDL_GetError());
    }

    if (SDL_RenderCopy(m_renderer, texture, NULL, &destination) < 0) {
        printf("Failed to render copy texture of map: %s", SDL_GetError());
    }
}