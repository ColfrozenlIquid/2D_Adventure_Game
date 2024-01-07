#include "cat.hpp"

Cat::Cat() {}

Cat::Cat(SDL_Renderer* sdl_renderer) {
    Entity::m_renderer = sdl_renderer;
    Entity::m_texture = load_Texture();
    Entity::m_x_pos = CAT_START_X;
    Entity::m_y_pos = CAT_START_Y;
    m_current_anim_state = 0;
}

Cat::~Cat() {}

void Cat::blit_Texture(int x_pos, int y_pos) {
    SDL_Rect destination;
    SDL_Rect source;

    destination.x = x_pos;
    destination.y = y_pos;
    destination.w = CAT_SPRITE_SIZE;
    destination.h = CAT_SPRITE_SIZE;

    source.x = m_current_anim_state * CAT_SPRITE_SIZE;
    source.y = 0;
    source.w = CAT_SPRITE_SIZE;
    source.h = CAT_SPRITE_SIZE;

    //std::cout << "Current blit texture is: " << m_texture << std::endl;
    //std::cout << "Trying to blit texture to renderer at: " << m_renderer << std::endl;

    // if (SDL_QueryTexture(m_texture, NULL, NULL, &destination.w, &destination.h) < 0) {
    //     printf("Failed to query texture of entity: %s", SDL_GetError());
    //     std::cout << "Texture is: " << m_texture << std::endl;
    // }

    if (SDL_RenderCopy(m_renderer, m_texture, &source, &destination) < 0) {
        printf("Failed to render copy of entity: %s", SDL_GetError());
    }
}

SDL_Texture* Cat::load_Texture() {
    SDL_Texture* texture;
    std::cout << "Loading Cat texture" << std::endl;
    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", Cat_SPRITE_PATH);
    texture = IMG_LoadTexture(m_renderer, CAT_SPRITE_PATH);
    std::cout << "Loaded texture at address: " << texture << std::endl;
    return texture;
}

void Cat::set_Animation_State(int state) {
    m_current_anim_state = state;
}