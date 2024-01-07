#include "devil.hpp"

Devil::Devil() {}

Devil::Devil(SDL_Renderer* sdl_renderer) {
    Entity::m_renderer = sdl_renderer;
    Entity::m_texture = load_Texture();
    Entity::m_x_pos = DEVIL_START_X;
    Entity::m_y_pos = DEVIL_START_Y;
}

Devil::~Devil() {}

SDL_Texture* Devil::load_Texture() {
    SDL_Texture* texture;
    std::cout << "Loading devil texture" << std::endl;
    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", DEVIL_SPRITE_PATH);
    texture = IMG_LoadTexture(m_renderer, DEVIL_SPRITE_PATH);
    std::cout << "Loaded texture at address: " << texture << std::endl;
    return texture;
}