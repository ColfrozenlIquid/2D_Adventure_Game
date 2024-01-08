#include "map.hpp"

#define FILENAME "./sprite/level/cobble0_"
#define WALL_SPRITE_PATH "./sprite/level/wall0_0.bmp"

Map::Map() {}

Map::Map(SDL_Renderer* sdl_renderer) : m_renderer(sdl_renderer) {
    init_Map();
    generate_Floor_Plan();
}

Map::~Map() {}

void Map::init_Map() {
    printf("Loading tiles\n");
    load_Tiles();
}

void Map::draw_Map() {
    for (int y = 0; y < MAP_RENDER_HEIGHT; y++) {
        for (int x = 0; x < MAP_RENDER_WIDTH; x++) {
            int type = m_map_data[y][x].type;
            int rotation = m_map_data[y][x].rotation;
            blit_Texture(m_tile_textures_arr[type], x * TILE_SIZE, y * TILE_SIZE, 0);
        }
    }
}

SDL_Texture* Map::load_Texture(std::string filename) {
    SDL_Texture* texture;
    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", filename);
    texture = IMG_LoadTexture(m_renderer, filename.c_str());
    std::cout << "Successfully loaded map texture: " << texture << std::endl;
    return texture;
}

void Map::load_Tiles() {
    for (int i = 0; i < MAX_TILE_TYPES; i++){
        std::string filename = FILENAME + std::to_string(i) + ".bmp";
        std::cout << "Trying to load texture: " << filename << std::endl;
        m_tile_textures_arr[i] = load_Texture(filename);
        std::cout << "Loading of texture: " << filename << " successful." << std::endl;
    }
}

void Map::blit_Texture(SDL_Texture* texture, int x_pos, int y_pos, int rotation) {
    SDL_Rect destination;
    destination.x = x_pos;
    destination.y = y_pos;

    //std::cout << "Trying to blit map texture to renderer at: " << m_renderer << std::endl;

    if (SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h) < 0) {
        printf("Failed to query texture of map: %s", SDL_GetError());
    }

    if (SDL_RenderCopyEx(m_renderer, texture, NULL, &destination, rotation, NULL, SDL_FLIP_NONE) < 0) {
        printf("Failed to render copy texture of map: %s", SDL_GetError());
    }
}

void Map::generate_Floor_Plan() {
    for (int i = 0; i < MAP_RENDER_HEIGHT; i++) {
        for (int j = 0; j < MAP_RENDER_WIDTH; j++) {
            if (i == 0) {
                m_map_data[i][j].type = 2;
                continue;
            }
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr_type(0, MAX_TILE_TYPES-2);
            std::uniform_int_distribution<> distr_rotation(0, 3);
            int type = distr_type(gen);
            int roation = distr_rotation(gen) * 90;
            m_map_data[i][j].type = type;
            m_map_data[i][j].rotation = roation;
        }
    }
}