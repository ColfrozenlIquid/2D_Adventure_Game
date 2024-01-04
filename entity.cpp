#include "entity.hpp"

Entity::Entity() {}

Entity::Entity(SDL_Renderer* sdl_renderer) : m_renderer(sdl_renderer) {
    m_texture = load_Texture(PLAYER_SPRITE);
}

Entity::~Entity() {}

SDL_Texture* Entity::load_Texture(std::string filename) {
    SDL_Texture* texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", filename);
    texture = IMG_LoadTexture(m_renderer, filename.c_str());
    return texture;
}

void Entity::blit_Texture(int x_pos, int y_pos) {
    SDL_Rect destination;
    destination.x = x_pos;
    destination.y = y_pos;

    if (SDL_QueryTexture(m_texture, NULL, NULL, &destination.w, &destination.h) < 0) {
        printf("Failed to query texture of entity: %s", SDL_GetError());
    }

    if (SDL_RenderCopy(m_renderer, m_texture, NULL, &destination) < 0) {
        printf("Failed to render copy of entity: %s", SDL_GetError());
    }
}