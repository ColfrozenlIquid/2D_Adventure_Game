#include "demon.hpp"

Demon::Demon() {}

Demon::Demon(SDL_Renderer* sdl_renderer) {
    Entity::m_renderer = sdl_renderer;
    Entity::m_texture = load_Texture();
    Entity::m_x_pos = DEMON_START_X;
    Entity::m_y_pos = DEMON_START_Y;
}

Demon::~Demon() {}

SDL_Texture* Demon::load_Texture() {
    SDL_Texture* texture;
    std::cout << "Loading Demon texture" << std::endl;
    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", Demon_SPRITE_PATH);
    texture = IMG_LoadTexture(m_renderer, DEMON_SPRITE_PATH);
    std::cout << "Loaded texture at address: " << texture << std::endl;
    return texture;
}