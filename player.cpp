#include "player.hpp"

Player::Player(SDL_Renderer* sdl_renderer) : m_renderer(sdl_renderer) {
    Entity::m_texture = load_Texture();
}

Player::~Player() {}

SDL_Texture* Player::load_Texture() {
    SDL_Texture* texture;
    std::cout << "Loading player texture" << std::endl;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", PLAYER_SPRITE_PATH);
    texture = IMG_LoadTexture(m_renderer, PLAYER_SPRITE_PATH);
    std::cout << "Loaded texture at address: " << texture << std::endl;
    return texture;
}