#include "chest.hpp"

Chest::Chest() {}

Chest::Chest(SDL_Renderer* sdl_renderer) {
    Entity::m_renderer = sdl_renderer;
    Entity::m_texture = load_Texture();
    Entity::m_x_pos = CHEST_START_X;
    Entity::m_y_pos = CHEST_START_Y;
}

Chest::~Chest() {}

SDL_Texture* Chest::load_Texture() {
    SDL_Texture* texture;
    std::cout << "Loading chest texture" << std::endl;
    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", CHEST_SPRITE_PATH);
    texture = IMG_LoadTexture(m_renderer, CHEST_SPRITE_PATH);
    std::cout << "Loaded texture at address: " << texture << std::endl;
    return texture;
}